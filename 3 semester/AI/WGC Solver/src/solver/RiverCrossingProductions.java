package solver;

import model.RiverSituation;
import model.Passenger;
import java.util.*;

/**
 * Конкретные продукции для задачи о переправе.
 */
public class RiverCrossingProductions {

    /**
     * Продукция: переправить фермера одного.
     */
    public static class MoveFarmerAlone implements ProductionRule {
        @Override
        public boolean isApplicable(RiverSituation situation) {
            // Фермер должен быть на берегу, где находится лодка
            Passenger farmer = situation.getFarmer();
            Set<Passenger> availableBank = situation.isBoatOnLeft() ?
                    situation.getLeftBank() : situation.getRightBank();
            return availableBank.contains(farmer);
        }

        @Override
        public RiverSituation apply(RiverSituation situation) {
            Passenger farmer = situation.getFarmer();
            Set<Passenger> move = new HashSet<>();
            move.add(farmer);
            return situation.executeMove(move);
        }

        @Override
        public int getCost() {
            return 1; // Базовая стоимость
        }

        @Override
        public String getDescription() {
            return "Фермер переправляется один";
        }
    }

    /**
     * Продукция: переправить фермера с пассажиром.
     */
    public static class MoveFarmerWithPassenger implements ProductionRule {
        private final Passenger passenger;

        public MoveFarmerWithPassenger(Passenger passenger) {
            this.passenger = passenger;
        }

        @Override
        public boolean isApplicable(RiverSituation situation) {
            // Проверяем базовые условия
            Passenger farmer = situation.getFarmer();
            Set<Passenger> availableBank = situation.isBoatOnLeft() ?
                    situation.getLeftBank() : situation.getRightBank();

            // Фермер и пассажир должны быть на одном берегу
            if (!availableBank.contains(farmer) || !availableBank.contains(passenger)) {
                return false;
            }

            // Проверяем вместимость лодки
            int boatCapacity = situation.getBoatCapacity();
            return 2 <= boatCapacity; // Фермер + 1 пассажир
        }

        @Override
        public RiverSituation apply(RiverSituation situation) {
            Passenger farmer = situation.getFarmer();
            Set<Passenger> move = new HashSet<>();
            move.add(farmer);
            move.add(passenger);
            return situation.executeMove(move);
        }

        @Override
        public int getCost() {
            // Стоимость зависит от типа пассажира
            if (passenger.getType().equals("predator")) {
                return 2; // Хищник - сложнее перевозить
            } else if (passenger.getType().equals("herbivore")) {
                return 3; // Травоядное - может съесть растения
            } else {
                return 1; // Растение - проще всего
            }
        }

        @Override
        public String getDescription() {
            return "Фермер переправляется с " + passenger.getName();
        }
    }

    /**
     * Продукция: переправить фермера с двумя пассажирами.
     */
    public static class MoveFarmerWithTwoPassengers implements ProductionRule {
        private final Passenger passenger1;
        private final Passenger passenger2;

        public MoveFarmerWithTwoPassengers(Passenger passenger1, Passenger passenger2) {
            this.passenger1 = passenger1;
            this.passenger2 = passenger2;
        }

        @Override
        public boolean isApplicable(RiverSituation situation) {
            Passenger farmer = situation.getFarmer();
            Set<Passenger> availableBank = situation.isBoatOnLeft() ?
                    situation.getLeftBank() : situation.getRightBank();

            // Все трое должны быть на одном берегу
            if (!availableBank.contains(farmer) ||
                    !availableBank.contains(passenger1) ||
                    !availableBank.contains(passenger2)) {
                return false;
            }

            // Проверяем вместимость лодки
            int boatCapacity = situation.getBoatCapacity();
            return 3 <= boatCapacity; // Фермер + 2 пассажира
        }

        @Override
        public RiverSituation apply(RiverSituation situation) {
            Passenger farmer = situation.getFarmer();
            Set<Passenger> move = new HashSet<>();
            move.add(farmer);
            move.add(passenger1);
            move.add(passenger2);
            return situation.executeMove(move);
        }

        @Override
        public int getCost() {
            // Комбинированная стоимость
            int cost = 2; // Базовая стоимость за сложность
            if (passenger1.getType().equals("predator") || passenger2.getType().equals("predator")) {
                cost += 1; // Хищники увеличивают сложность
            }
            if (passenger1.getType().equals("herbivore") || passenger2.getType().equals("herbivore")) {
                cost += 1; // Травоядные тоже
            }
            return cost;
        }

        @Override
        public String getDescription() {
            return "Фермер переправляется с " + passenger1.getName() +
                    " и " + passenger2.getName();
        }
    }

    /**
     * Фабрика для создания всех применимых продукций к состоянию.
     */
    public static List<ProductionRule> createApplicableRules(RiverSituation situation) {
        List<ProductionRule> rules = new ArrayList<>();

        // Продукция 1: фермер один
        rules.add(new MoveFarmerAlone());

        // Продукции 2: фермер с каждым пассажиром
        Set<Passenger> availableBank = situation.isBoatOnLeft() ?
                situation.getLeftBank() : situation.getRightBank();
        Passenger farmer = situation.getFarmer();

        for (Passenger passenger : availableBank) {
            if (!passenger.equals(farmer)) {
                rules.add(new MoveFarmerWithPassenger(passenger));
            }
        }

        // Продукции 3: фермер с двумя пассажирами (если позволяет вместимость)
        if (situation.getBoatCapacity() >= 3) {
            List<Passenger> otherPassengers = new ArrayList<>(availableBank);
            otherPassengers.remove(farmer);

            for (int i = 0; i < otherPassengers.size(); i++) {
                for (int j = i + 1; j < otherPassengers.size(); j++) {
                    rules.add(new MoveFarmerWithTwoPassengers(
                            otherPassengers.get(i),
                            otherPassengers.get(j)
                    ));
                }
            }
        }

        // Фильтруем только применимые правила
        List<ProductionRule> applicableRules = new ArrayList<>();
        for (ProductionRule rule : rules) {
            if (rule.isApplicable(situation)) {
                applicableRules.add(rule);
            }
        }

        return applicableRules;
    }
}