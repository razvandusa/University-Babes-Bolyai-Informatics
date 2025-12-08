package org.example.domain;

/**
 * Represents a Duck user in the social network.
 * Each duck has a type, speed, and resistance.
 */
public class Duck extends User {
    private DuckType duckType;
    private Double speed;
    private Double resistance;

    /**
     * Constructs a new Duck with the given parameters.
     *
     * @param id the unique identifier inherited from User
     * @param username the username of the Duck
     * @param email the email of the Duck
     * @param password the password of the Duck
     * @param duckType the type of the duck
     * @param speed the speed of the duck
     * @param resistance the resistance of the duck
     */
    public Duck(Long id, String userType, String username, String email, String password, DuckType duckType, Double speed, Double resistance) {
        super(id, userType, username, email, password);
        this.duckType = duckType;
        this.speed = speed;
        this.resistance = resistance;
    }

    public DuckType getDuckType() { return duckType; }
    public Double getSpeed() { return speed; }
    public Double getResistance() { return resistance; }

    public void setDuckType(DuckType duckType) { this.duckType = duckType; }
    public void setSpeed(Double speed) { this.speed = speed; }
    public void setResistance(Double resistance) { this.resistance = resistance; }

    @Override
    public String toString() {
        return "Duck{" +
                super.toString() +
                ", duckType=" + duckType +
                ", speed=" + speed +
                ", resistance=" + resistance +
                '}';
    }
}
