public class Q6Main {
    public static void main(String[] args) {

    }
}

class Address {
    private String premiseNumber;
    private String street;
    private String city;
    private int pin;
    private String state;

    Address(String number, String street, String city, String state, int pin) {
        premiseNumber = number;
        this.street = street;
        this.city = city;
        this.pin = pin;
        this.state = state;
    }

    Address() {
    }

    String getPremiseNumber() {
        return premiseNumber;
    }

    String getStreet() {
        return street;
    }

    String getCity() {
        return city;
    }

    int getPin() {
        return pin;
    }

    String getState() {
        return state;
    }

    void setPremisesNumber(String num) {
        premiseNumber = num;
    }

    void setStreet(String name) {
        street = name;
    }

    void setCity(String name) {
        city = name;
    }

    void setPin(int pin) {
        this.pin = pin;
    }

    void setState(String name) {
        state = name;
    }

    @Override
    public String toString() {
        String str = premiseNumber + ", " + street + ", " + city + ", " + state + "-" + Integer.toString(pin);

        return str;
    }
}
