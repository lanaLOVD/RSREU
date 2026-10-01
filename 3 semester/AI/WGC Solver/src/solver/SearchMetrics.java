package solver;

import java.util.*;

/**
 * Класс для сбора и анализа метрик поиска.
 * Отслеживает характеристики алгоритмов поиска.
 */
public class SearchMetrics {

    // Основные метрики
    private int depth;                    // Глубина поиска (макс. глубина рекурсии/пути)
    private int solutionLength;           // Длина найденного решения
    private int visitedNodes;             // Количество посещенных вершин (узлов)
    private int expandedNodes;            // Количество раскрытых вершин (порожденных детей)
    private double branchingFactor;       // Средняя разветвленность
    private double searchDirectionality;  // Направленность поиска (0-1)

    // Дополнительные метрики
    private long startTime;
    private long endTime;
    private int deadEnds;                 // Количество тупиков
    private int backtrackCount;           // Количество откатов
    private int maxMemoryUsage;          // Максимальное использование памяти (узлов в памяти)

    // Для вычисления разветвленности
    private List<Integer> branchSizes;

    // Для вычисления направленности
    private int heuristicImprovements;    // Улучшения эвристики
    private int heuristicWorsenings;      // Ухудшения эвристики

    public SearchMetrics() {
        reset();
    }

    public void reset() {
        depth = 0;
        solutionLength = 0;
        visitedNodes = 0;
        expandedNodes = 0;
        branchingFactor = 0.0;
        searchDirectionality = 0.5; // Нейтральное значение

        deadEnds = 0;
        backtrackCount = 0;
        maxMemoryUsage = 0;

        branchSizes = new ArrayList<>();
        heuristicImprovements = 0;
        heuristicWorsenings = 0;
    }

    public void startTimer() {
        startTime = System.currentTimeMillis();
    }

    public void stopTimer() {
        endTime = System.currentTimeMillis();
    }

    // Регистрация посещения узла
    public void nodeVisited() {
        visitedNodes++;
        updateMemoryUsage();
    }

    // Регистрация раскрытия узла (генерации потомков)
    public void nodeExpanded(int childrenCount) {
        expandedNodes++;
        branchSizes.add(childrenCount);
        updateMemoryUsage();
    }

    // Регистрация тупика
    public void deadEndEncountered() {
        deadEnds++;
    }

    // Регистрация отката
    public void backtrack() {
        backtrackCount++;
    }

    // Регистрация изменения глубины
    public void updateDepth(int currentDepth) {
        depth = Math.max(depth, currentDepth);
    }

    // Регистрация изменения эвристики (для направленности)
    public void heuristicChanged(int oldHeuristic, int newHeuristic) {
        if (newHeuristic < oldHeuristic) {
            heuristicImprovements++;
        } else if (newHeuristic > oldHeuristic) {
            heuristicWorsenings++;
        }
    }

    // Установка длины решения
    public void setSolutionLength(int length) {
        solutionLength = length;
    }

    // Расчет всех метрик
    public void calculateAllMetrics() {
        calculateBranchingFactor();
        calculateSearchDirectionality();
    }

    // Расчет средней разветвленности
    private void calculateBranchingFactor() {
        if (branchSizes.isEmpty()) {
            branchingFactor = 0.0;
            return;
        }

        double sum = 0.0;
        for (int size : branchSizes) {
            sum += size;
        }
        branchingFactor = sum / branchSizes.size();
    }

    // Расчет направленности поиска (0 - случайный, 1 - идеально направленный)
    private void calculateSearchDirectionality() {
        int totalChanges = heuristicImprovements + heuristicWorsenings;
        if (totalChanges == 0) {
            searchDirectionality = 0.5; // Нейтральное значение
            return;
        }

        // Формула направленности: улучшения / общие изменения
        searchDirectionality = (double) heuristicImprovements / totalChanges;
    }

    private void updateMemoryUsage() {
        int currentMemory = visitedNodes + expandedNodes;
        maxMemoryUsage = Math.max(maxMemoryUsage, currentMemory);
    }

    // Геттеры для метрик
    public int getDepth() { return depth; }
    public int getSolutionLength() { return solutionLength; }
    public int getVisitedNodes() { return visitedNodes; }
    public int getExpandedNodes() { return expandedNodes; }
    public double getBranchingFactor() { return branchingFactor; }
    public double getSearchDirectionality() { return searchDirectionality; }
    public int getDeadEnds() { return deadEnds; }
    public int getBacktrackCount() { return backtrackCount; }
    public int getMaxMemoryUsage() { return maxMemoryUsage; }
    public long getExecutionTime() { return endTime - startTime; }

    // Получение эффективности поиска
    public double getSearchEfficiency() {
        if (solutionLength == 0) return 0.0;
        return (double) solutionLength / visitedNodes;
    }

    // Получение полноты поиска
    public double getSearchCompleteness() {
        if (expandedNodes == 0) return 0.0;
        return (double) visitedNodes / expandedNodes;
    }

    // Форматированный вывод всех метрик
    public void printAllMetrics() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("МЕТРИКИ ПОИСКА");
        System.out.println("=".repeat(80));

        System.out.printf("%-30s: %d мс%n", "Время выполнения", getExecutionTime());
        System.out.printf("%-30s: %d%n", "Длина решения", solutionLength);
        System.out.printf("%-30s: %d%n", "Максимальная глубина", depth);
        System.out.printf("%-30s: %d%n", "Посещено вершин", visitedNodes);
        System.out.printf("%-30s: %d%n", "Раскрыто вершин", expandedNodes);
        System.out.printf("%-30s: %d%n", "Тупиков найдено", deadEnds);
        System.out.printf("%-30s: %d%n", "Откатов выполнено", backtrackCount);
        System.out.printf("%-30s: %d%n", "Макс. вершин в памяти", maxMemoryUsage);

        System.out.println("-".repeat(80));

        System.out.printf("%-30s: %.2f%n", "Средняя разветвленность", branchingFactor);
        System.out.printf("%-30s: %.3f (0-1)%n", "Направленность поиска", searchDirectionality);
        System.out.printf("%-30s: %.4f%n", "Эффективность поиска", getSearchEfficiency());
        System.out.printf("%-30s: %.2f%%%n", "Полнота поиска", getSearchCompleteness() * 100);

        // Интерпретация направленности
        System.out.println("-".repeat(80));
        System.out.println("ИНТЕРПРЕТАЦИЯ НАПРАВЛЕННОСТИ:");
        if (searchDirectionality >= 0.8) {
            System.out.println("  Отличная направленность! Поиск эффективно движется к цели.");
        } else if (searchDirectionality >= 0.6) {
            System.out.println("  Хорошая направленность. Поиск в основном улучшает состояние.");
        } else if (searchDirectionality >= 0.4) {
            System.out.println("  Средняя направленность. Есть как улучшения, так и ухудшения.");
        } else if (searchDirectionality >= 0.2) {
            System.out.println("  Слабая направленность. Поиск часто ухудшает состояние.");
        } else {
            System.out.println("  Очень слабая направленность. Поиск близок к случайному.");
        }

        System.out.println("=".repeat(80));
    }

    // Сравнение двух наборов метрик
    public static void compareMetrics(SearchMetrics m1, SearchMetrics m2, String name1, String name2) {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("СРАВНЕНИЕ МЕТРИК");
        System.out.println("=".repeat(80));

        System.out.printf("%-25s %-20s %-20s %-10s%n",
                "Метрика", name1, name2, "Разница");
        System.out.println("-".repeat(80));

        printComparisonRow("Время (мс)",
                m1.getExecutionTime(), m2.getExecutionTime(), false);
        printComparisonRow("Длина решения",
                m1.getSolutionLength(), m2.getSolutionLength(), false);
        printComparisonRow("Глубина",
                m1.getDepth(), m2.getDepth(), false);
        printComparisonRow("Посещено вершин",
                m1.getVisitedNodes(), m2.getVisitedNodes(), false);
        printComparisonRow("Разветвленность",
                m1.getBranchingFactor(), m2.getBranchingFactor(), true);
        printComparisonRow("Направленность",
                m1.getSearchDirectionality(), m2.getSearchDirectionality(), true);
        printComparisonRow("Эффективность",
                m1.getSearchEfficiency(), m2.getSearchEfficiency(), true);

        System.out.println("=".repeat(80));
    }

    private static void printComparisonRow(String metricName,
                                           double value1, double value2, boolean isDouble) {
        String format = isDouble ? "%.3f" : "%.0f";
        double diff = value2 - value1;
        String diffStr = String.format("%+.3f", diff);

        System.out.printf("%-25s %-20s %-20s %-10s%n",
                metricName,
                String.format(format, value1),
                String.format(format, value2),
                diffStr);
    }
}