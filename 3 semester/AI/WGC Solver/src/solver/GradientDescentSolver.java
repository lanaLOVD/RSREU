package solver;

import model.RiverSituation;
import model.Passenger;
import java.util.*;

/**
 * Градиентный спуск с оценочной функцией.
 * Алгоритм: всегда выбираем состояние с наилучшей эвристической оценкой,
 * подобно "жадному" поиску по градиенту.
 */
public class GradientDescentSolver {

    private static final int MAX_ITERATIONS = 1000;
    private static final int MAX_DEPTH = 50;

    /**
     * Решает задачу методом градиентного спуска.
     */
    public static List<RiverSituation> solve(RiverSituation initialSituation) {
        System.out.println("Запуск градиентного спуска с оценочной функцией...");
        long startTime = System.currentTimeMillis();

        // Используем DFS с эвристикой для реализации градиентного спуска
        List<RiverSituation> solution = gradientDescentSearch(initialSituation);

        long endTime = System.currentTimeMillis();
        System.out.println("Поиск завершен за " + (endTime - startTime) + " мс");

        return solution;
    }

    /**
     * Основной алгоритм градиентного спуска.
     */
    private static List<RiverSituation> gradientDescentSearch(RiverSituation initialSituation) {
        List<RiverSituation> currentPath = new ArrayList<>();
        currentPath.add(initialSituation);

        Set<String> visited = new HashSet<>();
        visited.add(getSituationKey(initialSituation));

        int iterations = 0;
        RiverSituation current = initialSituation;

        while (iterations < MAX_ITERATIONS && !current.isGoal()) {
            iterations++;

            // Получаем все возможные следующие состояния
            List<RiverSituation> candidates = generateCandidates(current);

            if (candidates.isEmpty()) {
                // Тупик - откат
                if (currentPath.size() <= 1) {
                    break; // Не можем откатиться дальше
                }
                currentPath.remove(currentPath.size() - 1);
                current = currentPath.get(currentPath.size() - 1);
                continue;
            }

            // Выбираем лучшего кандидата по эвристической оценке
            RiverSituation bestCandidate = null;
            int bestScore = Integer.MAX_VALUE;

            for (RiverSituation candidate : candidates) {
                if (!candidate.isSafe()) {
                    continue;
                }

                String key = getSituationKey(candidate);
                if (visited.contains(key)) {
                    continue; // Уже посещали
                }

                int score = evaluateState(candidate);
                if (score < bestScore) {
                    bestScore = score;
                    bestCandidate = candidate;
                }
            }

            if (bestCandidate == null) {
                // Не нашли хорошего кандидата - откат
                if (currentPath.size() <= 1) {
                    break;
                }
                currentPath.remove(currentPath.size() - 1);
                current = currentPath.get(currentPath.size() - 1);
                continue;
            }

            // Переходим к лучшему кандидату
            current = bestCandidate;
            currentPath.add(current);
            visited.add(getSituationKey(current));

            // Проверяем ограничение по глубине
            if (currentPath.size() > MAX_DEPTH) {
                // Слишком глубоко - откат
                currentPath.remove(currentPath.size() - 1);
                current = currentPath.get(currentPath.size() - 1);
            }
        }

        if (current.isGoal()) {
            return currentPath;
        } else {
            return new ArrayList<>();
        }
    }

    /**
     * Генерирует возможные следующие состояния из текущего.
     */
    private static List<RiverSituation> generateCandidates(RiverSituation situation) {
        List<RiverSituation> candidates = new ArrayList<>();

        for (ProductionRule rule : RiverCrossingProductions.createApplicableRules(situation)) {
            RiverSituation newSituation = rule.apply(situation);
            candidates.add(newSituation);
        }

        return candidates;
    }

    /**
     * Оценочная функция для градиентного спуска.
     * Чем МЕНЬШЕ значение, тем состояние ЛУЧШЕ.
     */
    private static int evaluateState(RiverSituation situation) {
        // Основной фактор: сколько пассажиров осталось на левом берегу
        int leftPassengers = situation.getLeftBank().size();

        // Штраф за опасные комбинации
        int dangerPenalty = calculateDangerPenalty(situation);

        // Бонус/штраф за положение лодки
        int boatPenalty = 0;
        if (!situation.isBoatOnLeft() && leftPassengers > 0) {
            boatPenalty = 2; // Лодка не там, где люди
        }

        // Эвристика минимального количества ходов
        int estimatedMoves = estimateMinimalMoves(situation);

        // Комбинированная оценка
        return leftPassengers * 10 +
                dangerPenalty * 5 +
                boatPenalty +
                estimatedMoves;
    }

    /**
     * Оценивает минимальное количество оставшихся ходов.
     */
    private static int estimateMinimalMoves(RiverSituation situation) {
        int leftCount = situation.getLeftBank().size();
        if (leftCount == 0) return 0;

        int boatCapacity = situation.getBoatCapacity();

        // Фермер должен вернуться за остальными, поэтому учитываем это
        int effectiveCapacity = Math.max(1, boatCapacity - 1);

        if (effectiveCapacity == 1) {
            // Только фермер может перевозить по одному пассажиру
            return leftCount * 2 - 1;
        } else {
            // Может перевозить несколько пассажиров
            int trips = (int) Math.ceil((double) leftCount / effectiveCapacity);
            return trips * 2 - 1;
        }
    }

    /**
     * Вычисляет штраф за опасные комбинации.
     */
    private static int calculateDangerPenalty(RiverSituation situation) {
        int penalty = 0;

        // Проверяем оба берега
        penalty += checkBankSafety(situation.getLeftBank());
        penalty += checkBankSafety(situation.getRightBank());

        return penalty;
    }

    private static int checkBankSafety(Set<Passenger> bank) {
        boolean hasFarmer = false;
        boolean hasPredator = false;
        boolean hasHerbivore = false;
        boolean hasPlant = false;

        for (Passenger p : bank) {
            switch (p.getType()) {
                case "farmer":
                    hasFarmer = true;
                    break;
                case "predator":
                    hasPredator = true;
                    break;
                case "herbivore":
                    hasHerbivore = true;
                    break;
                case "plant":
                    hasPlant = true;
                    break;
            }
        }

        // Если есть фермер, всё безопасно
        if (hasFarmer) {
            return 0;
        }

        int penalty = 0;
        if (hasPredator && hasHerbivore) {
            penalty += 2; // Хищник может съесть травоядное
        }
        if (hasHerbivore && hasPlant) {
            penalty += 1; // Травоядное может съесть растение
        }

        return penalty;
    }

    /**
     * Генерирует уникальный ключ для состояния.
     */
    private static String getSituationKey(RiverSituation situation) {
        List<String> leftNames = new ArrayList<>();
        for (Passenger p : situation.getLeftBank()) {
            leftNames.add(p.getName());
        }
        Collections.sort(leftNames);

        List<String> rightNames = new ArrayList<>();
        for (Passenger p : situation.getRightBank()) {
            rightNames.add(p.getName());
        }
        Collections.sort(rightNames);

        String boatSide = situation.isBoatOnLeft() ? "L" : "R";

        return "L:" + String.join(",", leftNames) +
                "|R:" + String.join(",", rightNames) +
                "|B:" + boatSide;
    }

    /**
     * Печатает решение.
     */
    public static void printSolution(List<RiverSituation> solution) {
        if (solution == null || solution.isEmpty()) {
            System.out.println("Решение не найдено методом градиентного спуска!");
            return;
        }

        System.out.println("\n" + "=".repeat(80));
        System.out.println("РЕШЕНИЕ МЕТОДОМ ГРАДИЕНТНОГО СПУСКА");
        System.out.println("=".repeat(80));
        System.out.println("Всего шагов: " + (solution.size() - 1));
        System.out.println("Длина пути: " + solution.size());

        for (int i = 0; i < solution.size(); i++) {
            System.out.println("\nШаг " + i + ":");
            System.out.println("  Состояние: " + solution.get(i));

            if (i > 0) {
                // Вычисляем разницу между шагами
                RiverSituation prev = solution.get(i-1);
                RiverSituation curr = solution.get(i);

                Set<Passenger> moved = new HashSet<>(prev.getLeftBank());
                moved.retainAll(curr.getRightBank());
                moved.addAll(prev.getRightBank());
                moved.retainAll(curr.getLeftBank());

                if (!moved.isEmpty()) {
                    System.out.println("  Переправлены: " + moved);
                }
            }
        }

        System.out.println("=".repeat(80));
    }
}