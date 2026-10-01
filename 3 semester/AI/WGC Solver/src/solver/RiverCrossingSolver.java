package solver;

import model.RiverSituation;
import model.Passenger;
import java.util.*;

public class RiverCrossingSolver {
    private AbstractSearchSolver searchAlgorithm;

    public RiverCrossingSolver(String algorithmType) {
        if ("DFS".equalsIgnoreCase(algorithmType)) {
            this.searchAlgorithm = new AbstractSearchSolver.DepthFirstSearch() {
                @Override
                protected boolean isGoalSituation(Object situation) {
                    return ((RiverSituation) situation).isGoal();
                }

                @Override
                protected boolean isValidSituation(Object situation) {
                    return ((RiverSituation) situation).isSafe();
                }

                @Override
                protected Set<Object> generateNextSituations(Object situation) {
                    RiverSituation riverSituation = (RiverSituation) situation;
                    Set<Object> nextSituations = new HashSet<>();

                    for (Set<Passenger> move : riverSituation.getPossibleMoves()) {
                        RiverSituation nextSituation = riverSituation.executeMove(move);
                        nextSituations.add(nextSituation);
                    }

                    return nextSituations;
                }
            };
        } else if ("BFS".equalsIgnoreCase(algorithmType)) {
            this.searchAlgorithm = new AbstractSearchSolver.BreadthFirstSearch() {
                @Override
                protected boolean isGoalSituation(Object situation) {
                    return ((RiverSituation) situation).isGoal();
                }

                @Override
                protected boolean isValidSituation(Object situation) {
                    return ((RiverSituation) situation).isSafe();
                }

                @Override
                protected Set<Object> generateNextSituations(Object situation) {
                    RiverSituation riverSituation = (RiverSituation) situation;
                    Set<Object> nextSituations = new HashSet<>();

                    for (Set<Passenger> move : riverSituation.getPossibleMoves()) {
                        RiverSituation nextSituation = riverSituation.executeMove(move);
                        nextSituations.add(nextSituation);
                    }

                    return nextSituations;
                }
            };
        } else if ("ASTAR".equalsIgnoreCase(algorithmType)) {
            this.searchAlgorithm = new AbstractSearchSolver.AStarSearch() {
                @Override
                protected boolean isGoalSituation(Object situation) {
                    return ((RiverSituation) situation).isGoal();
                }

                @Override
                protected boolean isValidSituation(Object situation) {
                    return ((RiverSituation) situation).isSafe();
                }

                @Override
                protected Set<Object> generateNextSituations(Object situation) {
                    RiverSituation riverSituation = (RiverSituation) situation;
                    Set<Object> nextSituations = new HashSet<>();

                    for (Set<Passenger> move : riverSituation.getPossibleMoves()) {
                        RiverSituation nextSituation = riverSituation.executeMove(move);
                        nextSituations.add(nextSituation);
                    }

                    return nextSituations;
                }

                @Override
                protected int heuristic(Object situation) {
                    RiverSituation riverSituation = (RiverSituation) situation;
                    return calculateHeuristic(riverSituation);
                }

                private int calculateHeuristic(RiverSituation situation) {
                    int passengersOnLeft = situation.getLeftBank().size();
                    int boatCapacity = situation.getBoatCapacity();

                    if (passengersOnLeft == 0) return 0;

                    if (passengersOnLeft == 1) return 1;

                    int passengersToMove = passengersOnLeft - 1;

                    if (boatCapacity <= 1) {
                        return passengersOnLeft * 2 - 1;
                    }

                    int trips = (int) Math.ceil((double) passengersToMove / (boatCapacity - 1));
                    return trips * 2 - 1;
                }
            };
        } else if (algorithmType.startsWith("DLS-")) {
            try {
                int depthLimit = Integer.parseInt(algorithmType.substring(4));
                this.searchAlgorithm = new AbstractSearchSolver.DepthLimitedSearch(depthLimit) {
                    @Override
                    protected boolean isGoalSituation(Object situation) {
                        return ((RiverSituation) situation).isGoal();
                    }

                    @Override
                    protected boolean isValidSituation(Object situation) {
                        return ((RiverSituation) situation).isSafe();
                    }

                    @Override
                    protected Set<Object> generateNextSituations(Object situation) {
                        RiverSituation riverSituation = (RiverSituation) situation;
                        Set<Object> nextSituations = new HashSet<>();

                        for (Set<Passenger> move : riverSituation.getPossibleMoves()) {
                            RiverSituation nextSituation = riverSituation.executeMove(move);
                            nextSituations.add(nextSituation);
                        }

                        return nextSituations;
                    }
                };
            } catch (NumberFormatException e) {
                throw new IllegalArgumentException("Неверный формат для DLS. Используйте DLS-X, где X - глубина.");
            }
        } else {
            throw new IllegalArgumentException("Неподдерживаемый тип алгоритма: " + algorithmType +
                    ". Используйте 'DFS', 'BFS', 'ASTAR' или 'DLS-X'.");
        }
    }

    public List<RiverSituation> solve(RiverSituation initialSituation) {
        List<Object> solution = searchAlgorithm.solve(initialSituation);

        List<RiverSituation> riverSolution = new ArrayList<>();
        for (Object situation : solution) {
            riverSolution.add((RiverSituation) situation);
        }

        return riverSolution;
    }

    public void printStatistics() {
        searchAlgorithm.printStatistics();
    }

    public int getSituationsExamined() {
        return searchAlgorithm.getSituationsExamined();
    }

    public long getTimeElapsed() {
        return searchAlgorithm.getTimeElapsed();
    }

    public boolean isSolutionFound() {
        return searchAlgorithm.isSolutionFound();
    }

    public static void compareAlgorithms(RiverSituation initialSituation, String... algorithms) {
        System.out.println("\n" + "=".repeat(60));
        System.out.println("СРАВНЕНИЕ АЛГОРИТМОВ ПОИСКА");
        System.out.println("=".repeat(60));

        List<AlgorithmResult> results = new ArrayList<>();

        for (String algorithm : algorithms) {
            System.out.println("\n--- " + algorithm + " ---");
            try {
                RiverCrossingSolver solver = new RiverCrossingSolver(algorithm);
                List<RiverSituation> solution = solver.solve(initialSituation);
                solver.printStatistics();

                results.add(new AlgorithmResult(
                        algorithm,
                        solver.getTimeElapsed(),
                        solver.getSituationsExamined(),
                        solution.size(),
                        solver.isSolutionFound()
                ));
            } catch (Exception e) {
                System.out.println("Ошибка при выполнении алгоритма " + algorithm + ": " + e.getMessage());
            }
        }

        printComparisonTable(results);
    }

    private static void printComparisonTable(List<AlgorithmResult> results) {
        System.out.println("\n" + "=".repeat(60));
        System.out.println("ИТОГИ СРАВНЕНИЯ АЛГОРИТМОВ");
        System.out.println("=".repeat(60));

        System.out.printf("%-15s %-12s %-15s %-12s %-10s%n",
                "Алгоритм", "Время (мс)", "Состояний", "Шагов", "Найдено");
        System.out.println("-".repeat(60));

        for (AlgorithmResult result : results) {
            System.out.printf("%-15s %-12d %-15d %-12d %-10s%n",
                    result.algorithm,
                    result.time,
                    result.situations,
                    result.steps,
                    result.found ? "Да" : "Нет");
        }
        System.out.println("=".repeat(60));
    }

    private static class AlgorithmResult {
        String algorithm;
        long time;
        int situations;
        int steps;
        boolean found;

        AlgorithmResult(String algorithm, long time, int situations, int steps, boolean found) {
            this.algorithm = algorithm;
            this.time = time;
            this.situations = situations;
            this.steps = steps;
            this.found = found;
        }
    }
}