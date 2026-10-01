package solver;

import model.RiverSituation;
import java.util.*;

/**
 * Продукционный подход к реализации процедур поиска решения.
 * Реализация на основе рекурсивного алгоритма с запоминанием состояний.
 */
public class ProductionBasedSolver {

    private static final int BOUND = 10000; // Ограничение на память
    private static int situationsExamined = 0;
    private static long startTime;

    /**
     * Основной метод решения.
     */
    public static List<RiverSituation> solve(RiverSituation initialSituation) {
        System.out.println("Запуск продукционного подхода...");
        startTime = System.currentTimeMillis();
        situationsExamined = 0;

        // Создаем начальный список состояний
        List<RiverSituation> situationList = new ArrayList<>();
        situationList.add(initialSituation);

        // Запускаем рекурсивный поиск
        SearchResult result = intelligentHeuristic(situationList);

        long endTime = System.currentTimeMillis();
        System.out.println("Поиск завершен за " + (endTime - startTime) + " мс");
        System.out.println("Проверено состояний: " + situationsExamined);

        if (result.success) {
            return result.solution;
        } else {
            return new ArrayList<>();
        }
    }

    /**
     * Результат поиска.
     */
    private static class SearchResult {
        boolean success;
        List<RiverSituation> solution;
        List<ProductionRule> rules;

        SearchResult(boolean success, List<RiverSituation> solution, List<ProductionRule> rules) {
            this.success = success;
            this.solution = solution;
            this.rules = rules;
        }

        static SearchResult success(List<RiverSituation> solution, List<ProductionRule> rules) {
            return new SearchResult(true, solution, rules);
        }

        static SearchResult failure() {
            return new SearchResult(false, new ArrayList<>(), new ArrayList<>());
        }
    }

    /**
     * Рекурсивная функция интеллектуального поиска.
     * Реализация алгоритма из описания.
     */
    private static SearchResult intelligentHeuristic(List<RiverSituation> situationList) {
        situationsExamined++;

        // 1. Выбираем первую ситуацию из списка
        RiverSituation currentSituation = situationList.get(0);

        // 2. Проверяем, не встречалась ли эта ситуация ранее
        if (isMember(currentSituation, situationList.subList(1, situationList.size()))) {
            return SearchResult.failure();
        }

        // 3. Проверяем, достигнута ли цель
        if (currentSituation.isGoal()) {
            return SearchResult.success(situationList, new ArrayList<>());
        }

        // 4. Проверяем, является ли состояние тупиковым
        if (isDeadEnd(currentSituation)) {
            return SearchResult.failure();
        }

        // 5. Проверяем ограничение памяти
        if (situationList.size() > BOUND) {
            return SearchResult.failure();
        }

        // 6. Получаем упорядоченные продукции
        List<ProductionRule> rules = appreciateRules(currentSituation);

        // 7. Цикл применения продукций
        for (int i = 0; i < rules.size(); i++) {
            ProductionRule rule = rules.get(i);

            // 8. Применяем продукцию
            RiverSituation newSituation = rule.apply(currentSituation);

            // 9. Проверяем безопасность нового состояния
            if (!newSituation.isSafe()) {
                continue;
            }

            // 10. Создаем новый список состояний
            List<RiverSituation> newSituationList = new ArrayList<>();
            newSituationList.add(newSituation);
            newSituationList.addAll(situationList);

            // 11. Рекурсивный вызов
            SearchResult result = intelligentHeuristic(newSituationList);

            // 12. Если успех, добавляем правило и возвращаем результат
            if (result.success) {
                List<ProductionRule> newRules = new ArrayList<>(result.rules);
                newRules.add(0, rule);
                return SearchResult.success(result.solution, newRules);
            }

            // 13. Если неудача, продолжаем цикл с следующей продукцией
        }

        // 14. Все продукции испробованы, неудача
        return SearchResult.failure();
    }

    /**
     * Проверяет, является ли состояние тупиковым.
     */
    private static boolean isDeadEnd(RiverSituation situation) {
        // Тупик, если нет безопасных ходов
        List<ProductionRule> rules = RiverCrossingProductions.createApplicableRules(situation);

        for (ProductionRule rule : rules) {
            RiverSituation newSituation = rule.apply(situation);
            if (newSituation.isSafe()) {
                return false; // Есть хотя бы один безопасный ход
            }
        }

        return true; // Нет безопасных ходов
    }

    /**
     * Проверяет, содержится ли состояние в списке.
     */
    private static boolean isMember(RiverSituation situation, List<RiverSituation> situationList) {
        for (RiverSituation s : situationList) {
            if (situationsEqual(situation, s)) {
                return true;
            }
        }
        return false;
    }

    /**
     * Сравнивает два состояния.
     */
    private static boolean situationsEqual(RiverSituation s1, RiverSituation s2) {
        return s1.getLeftBank().equals(s2.getLeftBank()) &&
                s1.getRightBank().equals(s2.getRightBank()) &&
                s1.isBoatOnLeft() == s2.isBoatOnLeft();
    }

    /**
     * Упорядочивает продукции с помощью оценочной функции.
     */
    private static List<ProductionRule> appreciateRules(RiverSituation situation) {
        List<ProductionRule> rules = RiverCrossingProductions.createApplicableRules(situation);

        // Сортируем по эвристической оценке результата применения
        rules.sort((r1, r2) -> {
            RiverSituation s1 = r1.apply(situation);
            RiverSituation s2 = r2.apply(situation);

            // Оценка: чем меньше пассажиров на левом берегу, тем лучше
            int score1 = s1.getLeftBank().size() * 10 + r1.getCost();
            int score2 = s2.getLeftBank().size() * 10 + r2.getCost();

            return Integer.compare(score1, score2);
        });

        return rules;
    }

    /**
     * Печатает решение.
     */
    public static void printSolution(List<RiverSituation> solution) {
        if (solution.isEmpty()) {
            System.out.println("Решение не найдено продукционным подходом!");
            return;
        }

        System.out.println("\n" + "=".repeat(80));
        System.out.println("РЕШЕНИЕ ПРОДУКЦИОННЫМ ПОДХОДОМ");
        System.out.println("=".repeat(80));
        System.out.println("Всего шагов: " + (solution.size() - 1));

        for (int i = 0; i < solution.size(); i++) {
            System.out.println("\nШаг " + i + ":");
            System.out.println("  " + solution.get(i));
        }

        System.out.println("=".repeat(80));
    }
}