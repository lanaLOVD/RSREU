package solver;

import model.RiverSituation;
import model.Passenger;
import java.util.Set;

public class Heuristics {

    public static int basicHeuristic(RiverSituation situation) {
        return situation.getLeftBank().size();
    }

    public static int capacityAwareHeuristic(RiverSituation situation) {
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

    public static int conflictAwareHeuristic(RiverSituation situation) {
        int baseHeuristic = capacityAwareHeuristic(situation);

        Set<Passenger> leftBank = situation.getLeftBank();
        int conflictPenalty = 0;

        boolean hasPredator = false;
        boolean hasHerbivore = false;
        boolean hasPlant = false;

        for (Passenger p : leftBank) {
            switch (p.getType()) {
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

        if (hasPredator && hasHerbivore) {
            conflictPenalty += 1;
        }

        if (hasHerbivore && hasPlant) {
            conflictPenalty += 1;
        }

        return baseHeuristic + conflictPenalty;
    }

    public static int manhattanHeuristic(RiverSituation situation) {
        int totalDistance = 0;

        for (Passenger p : situation.getAllPassengers()) {
            if (p.getType().equals("farmer")) continue;

            if (situation.getLeftBank().contains(p)) {
                totalDistance += 1;
            }
        }

        int boatCapacity = situation.getBoatCapacity();
        int passengersOnLeft = Math.max(0, situation.getLeftBank().size() - 1);

        if (passengersOnLeft > 0 && boatCapacity > 1) {
            int extraTrips = (int) Math.ceil((double) passengersOnLeft / (boatCapacity - 1)) - 1;
            totalDistance += extraTrips;
        }

        return totalDistance;
    }

    public static int combinedHeuristic(RiverSituation situation) {
        int h1 = basicHeuristic(situation);
        int h2 = capacityAwareHeuristic(situation);
        int h3 = conflictAwareHeuristic(situation);
        int h4 = manhattanHeuristic(situation);

        return Math.max(Math.max(h1, h2), Math.max(h3, h4));
    }

    public static boolean isAdmissible(RiverSituation situation, int heuristicValue) {
        int minPossibleCost = situation.getLeftBank().size();
        return heuristicValue >= minPossibleCost;
    }
}