package model;

import java.util.*;

public class GameRules {
    private final List<Passenger> allPassengers;
    private final int boatCapacity;

    public GameRules() {
        this.allPassengers = createDefaultPassengers();
        this.boatCapacity = 3;
    }

    public GameRules(int boatCapacity) {
        this.allPassengers = createDefaultPassengers();
        this.boatCapacity = boatCapacity;
    }

    private List<Passenger> createDefaultPassengers() {
        List<Passenger> passengers = new ArrayList<>();

        passengers.add(new Passenger("Фермер", "farmer", null));
        passengers.add(new Passenger("Волк", "predator", "herbivore"));
        passengers.add(new Passenger("Лиса", "predator", "herbivore"));
        passengers.add(new Passenger("Коза", "herbivore", "plant"));
        passengers.add(new Passenger("Курица", "herbivore", "plant"));
        passengers.add(new Passenger("Капуста", "plant", null));
        passengers.add(new Passenger("Зерно", "plant", null));

        return passengers;
    }

    public void addPassenger(String name, String type, String eats) {
        allPassengers.add(new Passenger(name, type, eats));
    }

    public void removePassenger(String name) {
        allPassengers.removeIf(p -> p.getName().equals(name));
    }

    public RiverSituation getInitialSituation() {
        return RiverSituation.createInitialSituation(allPassengers, boatCapacity);
    }

    public void printRules() {
        System.out.println("=".repeat(60));
        System.out.println("ПРАВИЛА ИГРЫ: ЗАДАЧА О ПЕРЕПРАВЕ ЧЕРЕЗ РЕКУ");
        System.out.println("=".repeat(60));
        System.out.println("Цель: Перевезти всех с левого берега на правый берег.");
        System.out.println("\nПравила:");
        System.out.println("1. Лодка вмещает до " + boatCapacity + " существ (включая фермера)");
        System.out.println("2. Фермер всегда должен быть в лодке, чтобы грести");
        System.out.println("3. Нельзя оставлять хищника с травоядным без присмотра");
        System.out.println("4. Нельзя оставлять травоядное с растением без присмотра");
        System.out.println("\nПассажиры (" + allPassengers.size() + "):");

        for (Passenger p : allPassengers) {
            String type = "";
            switch (p.getType()) {
                case "farmer": type = "фермер"; break;
                case "predator": type = "хищник"; break;
                case "herbivore": type = "травоядное"; break;
                case "plant": type = "растение"; break;
            }
            System.out.println("  " + p.getName() + " (" + type + ")");
        }

        System.out.println("\nКто кого ест:");
        for (Passenger p : allPassengers) {
            if (p.getEats() != null) {
                String eatsWhat = "";
                switch (p.getEats()) {
                    case "herbivore": eatsWhat = "травоядных"; break;
                    case "plant": eatsWhat = "растения"; break;
                }
                System.out.println("  " + p.getName() + " ест " + eatsWhat);
            }
        }
        System.out.println("=".repeat(60) + "\n");
    }

    public List<Passenger> getAllPassengers() {
        return new ArrayList<>(allPassengers);
    }

    public int getBoatCapacity() {
        return boatCapacity;
    }
}