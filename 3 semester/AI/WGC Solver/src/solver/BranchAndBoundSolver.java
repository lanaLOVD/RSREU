package solver;

import model.RiverSituation;
import model.Passenger;
import java.util.*;

//Реализация стратегии ветвей и границ.
//Использует оценочную функцию для выбора ветви с минимальной оценкой.
public class BranchAndBoundSolver {

    //g(n) - фактическая стоимость достижения узла
    //h(n) - эвристическая оценка до цели
    //f(n) = g(n) + h(n) - приоритет для выбора узла

    //Узел дерева поиска для Branch and Bound.
    private static class BBNode implements Comparable<BBNode> {
        RiverSituation situation;
        BBNode parent;
        ProductionRule rule;
        int pathCost; // g(n) - стоимость пути до этого узла
        int estimatedTotalCost; // f(n) = g(n) + h(n)

        BBNode(RiverSituation situation, BBNode parent, ProductionRule rule,
               int pathCost, int estimatedTotalCost) {
            this.situation = situation;
            this.parent = parent;
            this.rule = rule;
            this.pathCost = pathCost;
            this.estimatedTotalCost = estimatedTotalCost;
        }

        @Override
        public int compareTo(BBNode other) {
            // Сравниваем по оценке полной стоимости
            return Integer.compare(this.estimatedTotalCost, other.estimatedTotalCost);
        }
    }

    //Решает задачу методом ветвей и границ.
    public static List<RiverSituation> solve(RiverSituation initialSituation) {
        System.out.println("Запуск стратегии ветвей и границ...");
        long startTime = System.currentTimeMillis();

        // Приоритетная очередь для узлов, отсортированная по оценке
        PriorityQueue<BBNode> openSet = new PriorityQueue<>();
        Map<String, Integer> bestCosts = new HashMap<>(); // Лучшие стоимости для ситуаций

        // Начальный узел
        int initialHeuristic = heuristic(initialSituation);
        BBNode startNode = new BBNode(
                initialSituation, null, null,
                0, initialHeuristic // f(n) = g(n) + h(n) = 0 + h(initial)
        );

        openSet.add(startNode);
        bestCosts.put(getSituationKey(initialSituation), 0);

        int situationsExamined = 0;
        int maxSituations = 100000;

        while (!openSet.isEmpty() && situationsExamined < maxSituations) {
            situationsExamined++;

            // Извлекаем узел с наименьшей оценкой
            BBNode currentNode = openSet.poll();

            // Если достигли цели
            if (currentNode.situation.isGoal()) {
                long endTime = System.currentTimeMillis();
                System.out.println("Решение найдено за " + (endTime - startTime) + " мс");
                System.out.println("Проверено ситуаций: " + situationsExamined);
                return reconstructPath(currentNode);
            }

            // Проверяем безопасность ситуации
            if (!currentNode.situation.isSafe()) {
                continue; // Пропускаем небезопасные ситуации
            }

            // Получаем все применимые продукции
            List<ProductionRule> applicableRules =
                    RiverCrossingProductions.createApplicableRules(currentNode.situation);

            for (ProductionRule rule : applicableRules) {
                // Применяем правило
                RiverSituation nextSituation = rule.apply(currentNode.situation);
                String situationKey = getSituationKey(nextSituation);

                // Вычисляем стоимость пути до новой ситуации
                int newPathCost = currentNode.pathCost + rule.getCost();

                // Проверяем, не нашли ли мы лучший путь к этой ситуации
                if (bestCosts.containsKey(situationKey) &&
                        bestCosts.get(situationKey) <= newPathCost) {
                    continue; // Уже есть лучший путь
                }

                // Обновляем лучшую стоимость
                bestCosts.put(situationKey, newPathCost);

                // Вычисляем эвристику для новой ситуации
                int heuristicValue = heuristic(nextSituation);
                int estimatedTotalCost = newPathCost + heuristicValue;

                // Создаем новый узел
                BBNode nextNode = new BBNode(
                        nextSituation, currentNode, rule,
                        newPathCost, estimatedTotalCost
                );

                openSet.add(nextNode);
            }
        }

        long endTime = System.currentTimeMillis();
        System.out.println("Поиск завершен за " + (endTime - startTime) + " мс");
        System.out.println("Проверено ситуаций: " + situationsExamined);

        if (situationsExamined >= maxSituations) {
            System.out.println("Достигнут лимит проверенных ситуаций (" + maxSituations + ")");
        }

        return new ArrayList<>();
    }

    //Эвристическая функция для оценки ситуации.
    //Используется минимально возможное количество ходов.
    private static int heuristic(RiverSituation situation) {
        int passengersOnLeft = situation.getLeftBank().size();
        int boatCapacity = situation.getBoatCapacity();

        if (passengersOnLeft == 0) return 0;
        if (passengersOnLeft == 1) return 1;

        int passengersToMove = passengersOnLeft - 1; // минус фермер

        if (boatCapacity <= 1) {
            return passengersOnLeft * 2 - 1;
        }

        // Минимальное количество поездок
        int minTrips = (int) Math.ceil((double) passengersToMove / (boatCapacity - 1));
        return minTrips * 2 - 1; // Последняя поездка только в одну сторону
    }

    //Восстанавливает путь от конечного узла к начальному.
    private static List<RiverSituation> reconstructPath(BBNode goalNode) {
        List<RiverSituation> path = new ArrayList<>();
        BBNode current = goalNode;

        // Идем от цели к началу
        while (current != null) {
            path.add(0, current.situation); // Добавляем в начало
            current = current.parent;
        }

        return path;
    }

    //Генерирует ключ для ситуации.
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

    //Печатает статистику и решение.
    public static void printSolution(List<RiverSituation> solution) {
        if (solution.isEmpty()) {
            System.out.println("Решение не найдено методом ветвей и границ!");
            return;
        }

        System.out.println("\n" + "=".repeat(80));
        System.out.println("РЕШЕНИЕ МЕТОДОМ ВЕТВЕЙ И ГРАНИЦ");
        System.out.println("=".repeat(80));
        System.out.println("Всего шагов: " + (solution.size() - 1));

        int totalCost = 0;
        for (int i = 0; i < solution.size(); i++) {
            System.out.println("\nШаг " + i + ":");
            System.out.println("  Состояние: " + solution.get(i));

            if (i > 0) {
                // Можно добавить информацию о примененном правиле
                System.out.println("  Ход: " + i);
            }
        }

        System.out.println("\nОбщая стоимость пути: " + totalCost);
        System.out.println("=".repeat(80));
    }
}