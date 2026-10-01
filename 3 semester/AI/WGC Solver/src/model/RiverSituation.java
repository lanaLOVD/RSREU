package model;

import java.util.*;
import java.util.stream.Collectors;

public class RiverSituation {
    private final Set<Passenger> leftBank;
    private final Set<Passenger> rightBank;
    private final boolean boatOnLeft;
    private final int boatCapacity;

    public RiverSituation(Set<Passenger> leftBank, Set<Passenger> rightBank,
                          boolean boatOnLeft, int boatCapacity) {
        this.leftBank = new HashSet<>(leftBank);
        this.rightBank = new HashSet<>(rightBank);
        this.boatOnLeft = boatOnLeft;
        this.boatCapacity = boatCapacity;
    }

    public static RiverSituation createInitialSituation(List<Passenger> allPassengers, int boatCapacity) {
        Set<Passenger> left = new HashSet<>(allPassengers);
        Set<Passenger> right = new HashSet<>();
        return new RiverSituation(left, right, true, boatCapacity);
    }

    public boolean isSafe() {
        return isBankSafe(leftBank) && isBankSafe(rightBank);
    }

    private boolean isBankSafe(Set<Passenger> bank) {
        boolean hasFarmer = bank.stream().anyMatch(p -> p.getType().equals("farmer"));
        if (hasFarmer) return true;

        List<Passenger> passengers = new ArrayList<>(bank);

        for (int i = 0; i < passengers.size(); i++) {
            Passenger p1 = passengers.get(i);
            for (int j = 0; j < passengers.size(); j++) {
                if (i == j) continue;
                Passenger p2 = passengers.get(j);

                if (p1.getEats() != null && p1.getEats().equals(p2.getType())) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isGoal() {
        return leftBank.isEmpty() && !rightBank.isEmpty();
    }

    public Passenger getFarmer() {
        for (Passenger p : getAllPassengers()) {
            if (p.getType().equals("farmer")) {
                return p;
            }
        }
        return null;
    }

    public Set<Passenger> getAllPassengers() {
        Set<Passenger> all = new HashSet<>(leftBank);
        all.addAll(rightBank);
        return all;
    }

    public List<Set<Passenger>> getPossibleMoves() {
        List<Set<Passenger>> moves = new ArrayList<>();
        Passenger farmer = getFarmer();
        Set<Passenger> availableBank = boatOnLeft ? leftBank : rightBank;

        if (!availableBank.contains(farmer)) {
            return moves;
        }

        List<Passenger> others = new ArrayList<>(availableBank);
        others.remove(farmer);

        // Фермер один
        Set<Passenger> move1 = new HashSet<>();
        move1.add(farmer);
        moves.add(move1);

        // Фермер + 1 пассажир
        for (Passenger p : others) {
            Set<Passenger> move = new HashSet<>();
            move.add(farmer);
            move.add(p);
            if (move.size() <= boatCapacity) {
                moves.add(move);
            }
        }

        // Фермер + 2 пассажира (если позволяет вместимость)
        if (boatCapacity >= 3 && others.size() >= 2) {
            for (int i = 0; i < others.size(); i++) {
                for (int j = i + 1; j < others.size(); j++) {
                    Set<Passenger> move = new HashSet<>();
                    move.add(farmer);
                    move.add(others.get(i));
                    move.add(others.get(j));
                    if (move.size() <= boatCapacity) {
                        moves.add(move);
                    }
                }
            }
        }

        // Фермер + 3 пассажира
        if (boatCapacity >= 4 && others.size() >= 3) {
            for (int i = 0; i < others.size(); i++) {
                for (int j = i + 1; j < others.size(); j++) {
                    for (int k = j + 1; k < others.size(); k++) {
                        Set<Passenger> move = new HashSet<>();
                        move.add(farmer);
                        move.add(others.get(i));
                        move.add(others.get(j));
                        move.add(others.get(k));
                        if (move.size() <= boatCapacity) {
                            moves.add(move);
                        }
                    }
                }
            }
        }
        return moves;
    }

    public RiverSituation executeMove(Set<Passenger> move) {
        Passenger farmer = getFarmer();
        if (!move.contains(farmer)) {
            throw new IllegalArgumentException("Фермер должен быть в лодке!");
        }

        Set<Passenger> newLeft = new HashSet<>(leftBank);
        Set<Passenger> newRight = new HashSet<>(rightBank);

        Set<Passenger> fromBank = boatOnLeft ? newLeft : newRight;
        Set<Passenger> toBank = boatOnLeft ? newRight : newLeft;

        for (Passenger p : move) {
            fromBank.remove(p);
            toBank.add(p);
        }

        return new RiverSituation(newLeft, newRight, !boatOnLeft, boatCapacity);
    }

    public Set<Passenger> getLeftBank() { return new HashSet<>(leftBank); }
    public Set<Passenger> getRightBank() { return new HashSet<>(rightBank); }
    public boolean isBoatOnLeft() { return boatOnLeft; }
    public int getBoatCapacity() { return boatCapacity; }

    // ==================== КРАСИВЫЙ ВЫВОД ====================
    @Override
    public String toString() {
        String left = formatBank(leftBank);
        String right = formatBank(rightBank);
        String boatSide = boatOnLeft ? "СЛЕВА" : "СПРАВА";

        String status = isGoal() ? " ✅ ЦЕЛЬ ДОСТИГНУТА" :
                isSafe() ? " (безопасно)" : " ❌ ОПАСНО!";

        return String.format("""
                ┌────────────────────────────────────────────────────────────┐
                │ Левый берег:  %-45s │
                │ Правый берег: %-45s │
                │ Лодка: %s%s
                └────────────────────────────────────────────────────────────┘
                """,
                left, right, boatSide, status);
    }

    private String formatBank(Set<Passenger> bank) {
        if (bank.isEmpty()) {
            return "—— пусто ——";
        }
        // Сортируем по имени — порядок всегда одинаковый и логичный
        return bank.stream()
                .map(Passenger::getName)
                .sorted()
                .collect(Collectors.joining(", "));
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        RiverSituation other = (RiverSituation) obj;
        return boatOnLeft == other.boatOnLeft &&
                leftBank.equals(other.leftBank) &&
                rightBank.equals(other.rightBank);
    }

    @Override
    public int hashCode() {
        return Objects.hash(leftBank, rightBank, boatOnLeft);
    }
}