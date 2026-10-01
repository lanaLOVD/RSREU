package model;

public class Passenger {
    private final String name;
    private final String type;
    private final String eats;

    public Passenger(String name, String type, String eats) {
        this.name = name;
        this.type = type;
        this.eats = eats;
    }

    public String getName() { return name; }
    public String getType() { return type; }
    public String getEats() { return eats; }

    @Override
    public String toString() {
        return name;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Passenger other = (Passenger) obj;
        return name.equals(other.name);
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }
}