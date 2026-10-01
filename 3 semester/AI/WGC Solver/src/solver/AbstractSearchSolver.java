package solver;

import java.util.*;

public abstract class AbstractSearchSolver {
    protected long startTime;
    protected long endTime;
    protected int situationsExamined;
    protected boolean solutionFound;

    public AbstractSearchSolver() {
        this.situationsExamined = 0;
        this.solutionFound = false;
    }

    public abstract List<Object> solve(Object initialSituation);

    protected abstract boolean isGoalSituation(Object situation);

    protected abstract boolean isValidSituation(Object situation);

    protected abstract Set<Object> generateNextSituations(Object situation);

    protected abstract List<Object> reconstructPath(Object situation, Map<Object, Object> parentMap);

    public void printStatistics() {
        System.out.println("\n" + "=".repeat(60));
        System.out.println("СТАТИСТИКА РЕШЕНИЯ");
        System.out.println("=".repeat(60));
        System.out.println("Время выполнения: " + (endTime - startTime) + " мс");
        System.out.println("Проверено состояний: " + situationsExamined);
        System.out.println("Решение " + (solutionFound ? "найдено" : "не найдено"));
        System.out.println("=".repeat(60));
    }

    public static class DepthFirstSearch extends AbstractSearchSolver {
        private Stack<Object> currentPath;

        public DepthFirstSearch() {
            super();
            this.currentPath = new Stack<>();
        }

        @Override
        public List<Object> solve(Object initialSituation) {
            startTime = System.currentTimeMillis();
            boolean found = depthFirstSearch(initialSituation);
            endTime = System.currentTimeMillis();

            if (found) {
                solutionFound = true;
                return new ArrayList<>(currentPath);
            }
            return Collections.emptyList();
        }

        private boolean depthFirstSearch(Object situation) {
            situationsExamined++;

            if (currentPath.contains(situation)) {
                return false;
            }

            currentPath.push(situation);

            if (isGoalSituation(situation)) {
                return true;
            }

            if (!isValidSituation(situation)) {
                currentPath.pop();
                return false;
            }

            for (Object nextSituation : generateNextSituations(situation)) {
                boolean found = depthFirstSearch(nextSituation);
                if (found) {
                    return true;
                }
            }

            currentPath.pop();
            return false;
        }

        @Override
        protected boolean isGoalSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected boolean isValidSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected Set<Object> generateNextSituations(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected List<Object> reconstructPath(Object situation, Map<Object, Object> parentMap) {
            throw new UnsupportedOperationException("Для поиска в глубину этот метод не используется");
        }
    }

    public static class BreadthFirstSearch extends AbstractSearchSolver {
        private Map<Object, Object> parentMap;

        public BreadthFirstSearch() {
            super();
            this.parentMap = new HashMap<>();
        }

        @Override
        public List<Object> solve(Object initialSituation) {
            startTime = System.currentTimeMillis();

            Queue<Object> queue = new LinkedList<>();
            Set<Object> examinedSituations = new HashSet<>();

            queue.add(initialSituation);
            examinedSituations.add(initialSituation);
            parentMap.put(initialSituation, null);

            while (!queue.isEmpty()) {
                Object currentSituation = queue.poll();
                situationsExamined++;

                if (isGoalSituation(currentSituation)) {
                    endTime = System.currentTimeMillis();
                    solutionFound = true;
                    return reconstructPath(currentSituation, parentMap);
                }

                if (!isValidSituation(currentSituation)) {
                    continue;
                }

                for (Object nextSituation : generateNextSituations(currentSituation)) {
                    if (!isAncestor(currentSituation, nextSituation)) {
                        parentMap.put(nextSituation, currentSituation);
                        queue.add(nextSituation);
                    }
                }
            }

            endTime = System.currentTimeMillis();
            return Collections.emptyList();
        }

        private boolean isAncestor(Object situation, Object possibleAncestor) {
            Object current = situation;
            while (current != null) {
                if (current.equals(possibleAncestor)) {
                    return true;
                }
                current = parentMap.get(current);
            }
            return false;
        }

        @Override
        protected List<Object> reconstructPath(Object situation, Map<Object, Object> parentMap) {
            List<Object> path = new LinkedList<>();
            Object current = situation;

            while (current != null) {
                path.add(0, current);
                current = parentMap.get(current);
            }

            return path;
        }

        @Override
        protected boolean isGoalSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected boolean isValidSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected Set<Object> generateNextSituations(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }
    }

    public static class AStarSearch extends AbstractSearchSolver {
        private Map<Object, Object> parentMap;
        private Map<Object, Integer> gScore;
        private Map<Object, Integer> fScore;

        public AStarSearch() {
            super();
            this.parentMap = new HashMap<>();
            this.gScore = new HashMap<>();
            this.fScore = new HashMap<>();
        }

        @Override
        public List<Object> solve(Object initialSituation) {
            startTime = System.currentTimeMillis();

            PriorityQueue<NodeWithScore> openSet = new PriorityQueue<>();
            Set<Object> closedSet = new HashSet<>();

            gScore.put(initialSituation, 0);
            fScore.put(initialSituation, heuristic(initialSituation));

            openSet.add(new NodeWithScore(initialSituation, fScore.get(initialSituation)));
            parentMap.put(initialSituation, null);

            while (!openSet.isEmpty()) {
                NodeWithScore current = openSet.poll();
                Object currentSituation = current.situation;
                situationsExamined++;

                if (isGoalSituation(currentSituation)) {
                    endTime = System.currentTimeMillis();
                    solutionFound = true;
                    return reconstructPath(currentSituation, parentMap);
                }

                closedSet.add(currentSituation);

                for (Object neighbor : generateNextSituations(currentSituation)) {
                    if (closedSet.contains(neighbor)) {
                        continue;
                    }

                    if (!isValidSituation(neighbor)) {
                        continue;
                    }

                    int tentativeGScore = gScore.get(currentSituation) + getMoveCost(currentSituation, neighbor);

                    if (!gScore.containsKey(neighbor) || tentativeGScore < gScore.get(neighbor)) {
                        parentMap.put(neighbor, currentSituation);
                        gScore.put(neighbor, tentativeGScore);
                        fScore.put(neighbor, tentativeGScore + heuristic(neighbor));

                        if (!openSet.contains(new NodeWithScore(neighbor, 0))) {
                            openSet.add(new NodeWithScore(neighbor, fScore.get(neighbor)));
                        }
                    }
                }
            }

            endTime = System.currentTimeMillis();
            return Collections.emptyList();
        }

        protected int heuristic(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        protected int getMoveCost(Object fromSituation, Object toSituation) {
            return 1;
        }

        @Override
        protected List<Object> reconstructPath(Object situation, Map<Object, Object> parentMap) {
            List<Object> path = new LinkedList<>();
            Object current = situation;

            while (current != null) {
                path.add(0, current);
                current = parentMap.get(current);
            }

            return path;
        }

        @Override
        protected boolean isGoalSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected boolean isValidSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected Set<Object> generateNextSituations(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        private class NodeWithScore implements Comparable<NodeWithScore> {
            Object situation;
            int fScore;

            NodeWithScore(Object situation, int fScore) {
                this.situation = situation;
                this.fScore = fScore;
            }

            @Override
            public int compareTo(NodeWithScore other) {
                return Integer.compare(this.fScore, other.fScore);
            }

            @Override
            public boolean equals(Object obj) {
                if (this == obj) return true;
                if (obj == null || getClass() != obj.getClass()) return false;
                NodeWithScore other = (NodeWithScore) obj;
                return situation.equals(other.situation);
            }

            @Override
            public int hashCode() {
                return situation.hashCode();
            }
        }
    }

    public static class DepthLimitedSearch extends AbstractSearchSolver {
        private int depthLimit;
        private Stack<Object> currentPath;

        public DepthLimitedSearch(int depthLimit) {
            super();
            this.depthLimit = depthLimit;
            this.currentPath = new Stack<>();
        }

        @Override
        public List<Object> solve(Object initialSituation) {
            startTime = System.currentTimeMillis();
            boolean found = depthLimitedSearch(initialSituation, 0);
            endTime = System.currentTimeMillis();

            if (found) {
                solutionFound = true;
                return new ArrayList<>(currentPath);
            }
            return Collections.emptyList();
        }

        private boolean depthLimitedSearch(Object situation, int depth) {
            situationsExamined++;

            if (depth > depthLimit) {
                return false;
            }

            if (currentPath.contains(situation)) {
                return false;
            }

            currentPath.push(situation);

            if (isGoalSituation(situation)) {
                return true;
            }

            if (!isValidSituation(situation)) {
                currentPath.pop();
                return false;
            }

            for (Object nextSituation : generateNextSituations(situation)) {
                boolean found = depthLimitedSearch(nextSituation, depth + 1);
                if (found) {
                    return true;
                }
            }

            currentPath.pop();
            return false;
        }

        @Override
        protected boolean isGoalSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected boolean isValidSituation(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected Set<Object> generateNextSituations(Object situation) {
            throw new UnsupportedOperationException("Метод должен быть реализован в конкретном классе");
        }

        @Override
        protected List<Object> reconstructPath(Object situation, Map<Object, Object> parentMap) {
            throw new UnsupportedOperationException("Для поиска с ограничением глубины этот метод не используется");
        }
    }

    public int getSituationsExamined() {
        return situationsExamined;
    }

    public long getTimeElapsed() {
        return endTime - startTime;
    }

    public boolean isSolutionFound() {
        return solutionFound;
    }
}