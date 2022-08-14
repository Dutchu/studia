import java.util.Objects;

public class PhoneNumber implements Comparable<PhoneNumber> {
    private long direction;
    private long number;

    public PhoneNumber(long direction, long number) {
        this.direction = direction;
        this.number = number;
    }

    public long getDirection() {
        return direction;
    }

    public long getNumber() {
        return number;
    }

    public void setDirection(long direction) {
        this.direction = direction;
    }

    public void setNumber(long number) {
        this.number = number;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        PhoneNumber that = (PhoneNumber) o;
        return direction == that.direction && number == that.number;
    }

    @Override
    public int hashCode() {
        return Objects.hash(direction, number);
    }

    @Override
    public int compareTo(PhoneNumber otherNumber) {
        return Long.compare(this.number, otherNumber.getNumber());
    }

    @Override
    public String toString() {
        return "PhoneNumber{" +
                "direction=" + direction +
                ", number=" + number +
                '}';
    }
}
