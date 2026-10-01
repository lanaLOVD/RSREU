// ┌───────────────────────────────────────────────────────────────┐
// │ Название программы : Универсальный решатель задач             │
// │ Предметная область : Классическая задача "Волк, коза, капуста"│
// │ Программист        : Соколова С.И.                            │
// │ Версия             : v.01.03.2026  (улучшенный вывод)        │
// │ Модули             : стандартные библиотеки Java (java.util)  │
// └───────────────────────────────────────────────────────────────┘

import model.GameRules;
import model.RiverSituation;
import model.Passenger;
import solver.*;
import java.util.*;
import view.SolutionVisualizer;
import javax.swing.JOptionPane;

public class Main {
    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        System.out.println("=".repeat(80));
        System.out.println("    ПРОДВИНУТЫЙ РЕШАТЕЛЬ ЗАДАЧИ О ПЕРЕПРАВЕ");
        System.out.println("              (улучшенный красивый вывод)");
        System.out.println("=".repeat(80));

        boolean exit = false;

        while (!exit) {
            printMenu();
            int choice = getIntInput("Ваш выбор: ", 1, 6);

            switch (choice) {
                case 1:
                    solveWithChosenMethod();
                    break;
                case 2:
                    compareAllMethods();
                    break;
                case 3:
                    demonstrateProductions();
                    break;
                case 4:
                    testComplexProblem();
                    break;
                case 5:
                    manualTesting();
                    break;
                case 6:
                    exit = true;
                    System.out.println("До свидания!");
                    break;
            }

            if (!exit) {
                System.out.println("\n" + "=".repeat(80));
                System.out.print("Нажмите Enter для продолжения...");
                scanner.nextLine();
            }
        }

        scanner.close();
    }

    private static void printMenu() {
        System.out.println("\nГЛАВНОЕ МЕНЮ:");
        System.out.println("1. Решить задачу (выбрать метод)");
        System.out.println("2. Сравнить все методы поиска");
        System.out.println("3. Демонстрация продукций");
        System.out.println("4. Тест сложной задачи");
        System.out.println("5. Ручное тестирование");
        System.out.println("6. Выход");
    }

    // ==================== НОВЫЙ УНИВЕРСАЛЬНЫЙ МЕТОД ====================
    private static void solveWithChosenMethod() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("         🎯 РЕШЕНИЕ ЗАДАЧИ С ВЫБОРОМ МЕТОДА");
        System.out.println("=".repeat(80));

        RiverSituation initialSituation = createProblem();
        System.out.println("📋 Начальная ситуация:");
        System.out.println(initialSituation);

        System.out.println("\n🔍 Выберите метод решения:");
        System.out.println("┌────┬────────────────────────────────────────┐");
        System.out.println("│ 1  │ Ветви и границы (Branch and Bound)     │");
        System.out.println("│ 2  │ Градиентный спуск                      │");
        System.out.println("│ 3  │ Продукционный подход                   │");
        System.out.println("│ 4  │ Поиск в глубину (DFS)                  │");
        System.out.println("│ 5  │ Поиск в ширину (BFS)                   │");
        System.out.println("│ 6  │ A* (звёздочка)                         │");
        System.out.println("└────┴────────────────────────────────────────┘");

        int methodChoice = getIntInput("Ваш выбор (1-6): ", 1, 6);

        List<RiverSituation> solution = null;
        String methodName = "";
        long startTime = System.currentTimeMillis();
        int visitedStates = 0;

        switch (methodChoice) {
            case 1:
                solution = BranchAndBoundSolver.solve(initialSituation);
                methodName = "Ветви и границы";
                break;
            case 2:
                solution = GradientDescentSolver.solve(initialSituation);
                methodName = "Градиентный спуск";
                break;
            case 3:
                solution = ProductionBasedSolver.solve(initialSituation);
                methodName = "Продукционный подход";
                break;
            case 4:
                RiverCrossingSolver dfsSolver = new RiverCrossingSolver("DFS");
                solution = dfsSolver.solve(initialSituation);
                visitedStates = dfsSolver.getSituationsExamined();
                methodName = "Поиск в глубину (DFS)";
                break;
            case 5:
                RiverCrossingSolver bfsSolver = new RiverCrossingSolver("BFS");
                solution = bfsSolver.solve(initialSituation);
                visitedStates = bfsSolver.getSituationsExamined();
                methodName = "Поиск в ширину (BFS)";
                break;
            case 6:
                RiverCrossingSolver astarSolver = new RiverCrossingSolver("ASTAR");
                solution = astarSolver.solve(initialSituation);
                visitedStates = astarSolver.getSituationsExamined();
                methodName = "A* (звёздочка)";
                break;
        }

        long time = System.currentTimeMillis() - startTime;

        if (solution == null || solution.isEmpty()) {
            System.out.println("\n❌ Решение НЕ найдено методом " + methodName);
            JOptionPane.showMessageDialog(null,
                    "Решение не найдено!\nПопробуйте другой алгоритм.",
                    "Решение не найдено",
                    JOptionPane.WARNING_MESSAGE);
            return;
        }

        // Красивый вывод в консоль
        System.out.println("\n" + "=".repeat(80));
        System.out.println("✨ РЕШЕНИЕ НАЙДЕНО! ✨");
        System.out.println("=".repeat(80));
        System.out.println("📐 Метод: " + methodName);
        System.out.println("⏱ Время: " + time + " мс");
        System.out.println("📏 Длина решения: " + (solution.size() - 1) + " шагов");
        if (visitedStates > 0) {
            System.out.println("📍 Посещено состояний: " + visitedStates);
        }
        System.out.println("🎨 Открывается графическая визуализация...");
        System.out.println("=".repeat(80));

        // Запускаем визуализатор
        new view.SolutionVisualizer(solution, methodName, time, visitedStates);
    }

    // ==================== КРАСИВЫЙ ВЫВОД РЕШЕНИЯ ====================
    private static void printNiceSolution(List<RiverSituation> solution, String methodName, long timeMs) {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("🎯 РЕШЕНИЕ МЕТОДОМ: " + methodName.toUpperCase());
        System.out.println("=".repeat(80));
        System.out.println("⏱ Время выполнения: " + timeMs + " мс");
        System.out.println("📏 Длина решения: " + (solution.size() - 1) + " шагов");
        System.out.println("🎨 Открывается графическое окно визуализации...");
        System.out.println("=".repeat(80));

        if (solution == null || solution.isEmpty()) {
            System.out.println("❌ Решение НЕ найдено!");
            JOptionPane.showMessageDialog(null,
                    "Решение не найдено!\nПопробуйте другой алгоритм или измените параметры задачи.",
                    "Решение не найдено",
                    JOptionPane.WARNING_MESSAGE);
            return;
        }

        // Запускаем новый универсальный визуализатор
        // Для получения количества посещённых состояний нужно передать статистику
        // Пока передаём 0, так как эта информация есть в другом месте
        new view.SolutionVisualizer(solution, methodName, timeMs, 0);
    }

    // ==================== СРАВНЕНИЕ ВСЕХ МЕТОДОВ (без изменений) ====================
    private static void compareAllMethods() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("    СРАВНЕНИЕ ВСЕХ МЕТОДОВ ПОИСКА");
        System.out.println("=".repeat(80));

        RiverSituation initialSituation = createProblem();
        System.out.println("📋 Тестовая задача: " + initialSituation.getClass().getSimpleName());
        System.out.println("🚣 Вместимость лодки: " + initialSituation.getBoatCapacity());

        // Структура для хранения результатов
        class Result {
            String name;
            long time;
            int steps;
            int visited;
            boolean found;
            List<RiverSituation> solution;

            Result(String name) { this.name = name; }
        }

        List<Result> results = new ArrayList<>();

        // 1. Ветви и границы
        System.out.println("\n🔄 Запуск: Ветви и границы...");
        Result r1 = new Result("Ветви и границы");
        long start = System.currentTimeMillis();
        r1.solution = BranchAndBoundSolver.solve(initialSituation);
        r1.time = System.currentTimeMillis() - start;
        r1.found = !r1.solution.isEmpty();
        r1.steps = r1.found ? r1.solution.size() - 1 : 0;
        results.add(r1);

        // 2. Градиентный спуск
        System.out.println("🔄 Запуск: Градиентный спуск...");
        Result r2 = new Result("Градиентный спуск");
        start = System.currentTimeMillis();
        r2.solution = GradientDescentSolver.solve(initialSituation);
        r2.time = System.currentTimeMillis() - start;
        r2.found = !r2.solution.isEmpty();
        r2.steps = r2.found ? r2.solution.size() - 1 : 0;
        results.add(r2);

        // 3. Продукционный подход
        System.out.println("🔄 Запуск: Продукционный подход...");
        Result r3 = new Result("Продукционный подход");
        start = System.currentTimeMillis();
        r3.solution = ProductionBasedSolver.solve(initialSituation);
        r3.time = System.currentTimeMillis() - start;
        r3.found = !r3.solution.isEmpty();
        r3.steps = r3.found ? r3.solution.size() - 1 : 0;
        results.add(r3);

        // 4. DFS
        System.out.println("🔄 Запуск: Поиск в глубину (DFS)...");
        Result r4 = new Result("Поиск в глубину");
        RiverCrossingSolver dfsSolver = new RiverCrossingSolver("DFS");
        start = System.currentTimeMillis();
        r4.solution = dfsSolver.solve(initialSituation);
        r4.time = System.currentTimeMillis() - start;
        r4.found = !r4.solution.isEmpty();
        r4.steps = r4.found ? r4.solution.size() - 1 : 0;
        r4.visited = dfsSolver.getSituationsExamined();
        results.add(r4);

        // 5. BFS
        System.out.println("🔄 Запуск: Поиск в ширину (BFS)...");
        Result r5 = new Result("Поиск в ширину");
        RiverCrossingSolver bfsSolver = new RiverCrossingSolver("BFS");
        start = System.currentTimeMillis();
        r5.solution = bfsSolver.solve(initialSituation);
        r5.time = System.currentTimeMillis() - start;
        r5.found = !r5.solution.isEmpty();
        r5.steps = r5.found ? r5.solution.size() - 1 : 0;
        r5.visited = bfsSolver.getSituationsExamined();
        results.add(r5);

        // Вывод красивой таблицы
        System.out.println("\n" + "=".repeat(80));
        System.out.println("                    📊 ИТОГИ СРАВНЕНИЯ АЛГОРИТМОВ");
        System.out.println("=".repeat(80));

        System.out.printf("┌──────────────────────┬────────────┬────────────┬──────────────┬────────────┐\n");
        System.out.printf("│ %-20s │ %-10s │ %-10s │ %-12s │ %-10s │\n",
                "Алгоритм", "Время (мс)", "Шагов", "Состояний", "Найдено");
        System.out.printf("├──────────────────────┼────────────┼────────────┼──────────────┼────────────┤\n");

        for (Result r : results) {
            String visitedStr = r.visited > 0 ? String.valueOf(r.visited) : "—";
            System.out.printf("│ %-20s │ %-10d │ %-10d │ %-12s │ %-10s │\n",
                    r.name, r.time, r.steps, visitedStr, r.found ? "✅ Да" : "❌ Нет");
        }

        System.out.printf("└──────────────────────┴────────────┴────────────┴──────────────┴────────────┘\n");
        System.out.println("=".repeat(80));

        // Спрашиваем, хотим ли посмотреть визуализацию какого-либо решения
        System.out.println("\n🎨 Хотите визуализировать решение?");
        System.out.println("1. Ветви и границы");
        System.out.println("2. Градиентный спуск");
        System.out.println("3. Продукционный подход");
        System.out.println("4. Поиск в глубину (DFS)");
        System.out.println("5. Поиск в ширину (BFS)");
        System.out.println("0. Нет, выйти в меню");

        int choice = getIntInput("Ваш выбор (0-5): ", 0, 5);

        if (choice >= 1 && choice <= 5) {
            Result selected = results.get(choice - 1);
            if (selected.found && !selected.solution.isEmpty()) {
                new view.SolutionVisualizer(selected.solution, selected.name,
                        selected.time, selected.visited);
            } else {
                System.out.println("❌ Для этого алгоритма решение не найдено!");
            }
        }
    }

    private static void printComparisonRow(String method, long time, List<RiverSituation> solution) {
        System.out.printf("%-25s %-12d %-12d %-10s%n",
                method,
                time,
                solution.isEmpty() ? 0 : solution.size() - 1,
                solution.isEmpty() ? "Нет" : "Да");
    }

    private static void demonstrateProductions() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("ДЕМОНСТРАЦИЯ ПРОДУКЦИЙ (ПРАВИЛ)");
        System.out.println("=".repeat(80));

        List<Passenger> passengers = new ArrayList<>();
        passengers.add(new Passenger("Фермер", "farmer", null));
        passengers.add(new Passenger("Волк", "predator", "herbivore"));
        passengers.add(new Passenger("Коза", "herbivore", "plant"));

        RiverSituation situation = RiverSituation.createInitialSituation(passengers, 2);

        System.out.println("Ситуация: " + situation);
        System.out.println("\nПрименимые продукции:");

        List<ProductionRule> rules = RiverCrossingProductions.createApplicableRules(situation);

        for (int i = 0; i < rules.size(); i++) {
            ProductionRule rule = rules.get(i);
            System.out.println("\n" + (i+1) + ". " + rule.getDescription());
            System.out.println("   Стоимость: " + rule.getCost());

            RiverSituation newSituation = rule.apply(situation);
            System.out.println("   Результат: " + newSituation);
            System.out.println("   Безопасно: " + newSituation.isSafe());
        }

        System.out.println("\nВсего применимых продукций: " + rules.size());
    }

    private static void testComplexProblem() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("ТЕСТ СЛОЖНОЙ ЗАДАЧИ");
        System.out.println("=".repeat(80));

        List<Passenger> passengers = new ArrayList<>();
        passengers.add(new Passenger("Фермер", "farmer", null));
        passengers.add(new Passenger("Волк", "predator", "herbivore"));
        passengers.add(new Passenger("Лиса", "predator", "herbivore"));
        passengers.add(new Passenger("Коза", "herbivore", "plant"));
        passengers.add(new Passenger("Курица", "herbivore", "plant"));
        passengers.add(new Passenger("Капуста", "plant", null));

        int capacity = getIntInput("Вместимость лодки (2-4): ", 2, 4);
        RiverSituation situation = RiverSituation.createInitialSituation(passengers, capacity);

        System.out.println("\nЗадача:");
        System.out.println("Пассажиры: " + passengers.size());
        System.out.println("Вместимость лодки: " + capacity);
        System.out.println("Начальная ситуация:");
        System.out.println(situation);

        System.out.println("\nТестирование градиентного спуска...");
        long start = System.currentTimeMillis();
        List<RiverSituation> solution = GradientDescentSolver.solve(situation);
        long time = System.currentTimeMillis() - start;

        printNiceSolution(solution, "Градиентный спуск", time);
    }

    private static void manualTesting() {
        System.out.println("\n" + "=".repeat(80));
        System.out.println("РУЧНОЕ ТЕСТИРОВАНИЕ");
        System.out.println("=".repeat(80));

        List<Passenger> passengers = new ArrayList<>();
        passengers.add(new Passenger("Фермер", "farmer", null));

        System.out.println("\nДобавьте пассажиров (0 — закончить):");
        System.out.println("1. Волк     2. Лиса     3. Коза     4. Курица");
        System.out.println("5. Капуста  6. Зерно    0. Готово");

        boolean adding = true;
        while (adding) {
            int choice = getIntInput("Выберите пассажира (0-6): ", 0, 6);
            switch (choice) {
                case 0: adding = false; break;
                case 1: passengers.add(new Passenger("Волк", "predator", "herbivore")); break;
                case 2: passengers.add(new Passenger("Лиса", "predator", "herbivore")); break;
                case 3: passengers.add(new Passenger("Коза", "herbivore", "plant")); break;
                case 4: passengers.add(new Passenger("Курица", "herbivore", "plant")); break;
                case 5: passengers.add(new Passenger("Капуста", "plant", null)); break;
                case 6: passengers.add(new Passenger("Зерно", "plant", null)); break;
            }
            System.out.println("Пассажиров: " + (passengers.size() - 1));
        }

        int capacity = getIntInput("\nВместимость лодки (2-4): ", 2, 4);

        System.out.println("\nВыберите метод решения:");
        System.out.println("1. Ветви и границы");
        System.out.println("2. Градиентный спуск");
        System.out.println("3. Продукционный подход");

        int methodChoice = getIntInput("Ваш выбор (1-3): ", 1, 3);

        RiverSituation situation = RiverSituation.createInitialSituation(passengers, capacity);
        System.out.println("\nНачальная ситуация:");
        System.out.println(situation);

        List<RiverSituation> solution = null;
        String methodName = "";

        switch (methodChoice) {
            case 1:
                solution = BranchAndBoundSolver.solve(situation);
                methodName = "Ветви и границы";
                break;
            case 2:
                solution = GradientDescentSolver.solve(situation);
                methodName = "Градиентный спуск";
                break;
            case 3:
                solution = ProductionBasedSolver.solve(situation);
                methodName = "Продукционный подход";
                break;
        }

        printNiceSolution(solution, methodName, 0);
    }

    private static RiverSituation createProblem() {
        System.out.println("\nВыберите задачу:");
        System.out.println("1. Классическая (Волк, Коза, Капуста)");
        System.out.println("2. Средняя (5 пассажиров)");
        System.out.println("3. Сложная (7 пассажиров)");

        int choice = getIntInput("Ваш выбор (1-3): ", 1, 3);

        switch (choice) {
            case 1:
                List<Passenger> classic = new ArrayList<>();
                classic.add(new Passenger("Фермер", "farmer", null));
                classic.add(new Passenger("Волк", "predator", "herbivore"));
                classic.add(new Passenger("Коза", "herbivore", "plant"));
                classic.add(new Passenger("Капуста", "plant", null));
                return RiverSituation.createInitialSituation(classic, 2);

            case 2:
                List<Passenger> medium = new ArrayList<>();
                medium.add(new Passenger("Фермер", "farmer", null));
                medium.add(new Passenger("Волк", "predator", "herbivore"));
                medium.add(new Passenger("Лиса", "predator", "herbivore"));
                medium.add(new Passenger("Коза", "herbivore", "plant"));
                medium.add(new Passenger("Капуста", "plant", null));
                return RiverSituation.createInitialSituation(medium, 3);

            case 3:
            default:
                GameRules rules = new GameRules(3);
                return rules.getInitialSituation();
        }
    }

    private static int getIntInput(String prompt, int min, int max) {
        int value = 0;
        boolean valid = false;

        while (!valid) {
            try {
                System.out.print(prompt);
                value = Integer.parseInt(scanner.nextLine().trim());
                if (value >= min && value <= max) {
                    valid = true;
                } else {
                    System.out.println("Пожалуйста, введите число от " + min + " до " + max);
                }
            } catch (NumberFormatException e) {
                System.out.println("Пожалуйста, введите целое число.");
            }
        }
        return value;
    }
}