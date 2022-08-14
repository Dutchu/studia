public class PersonEntity extends Entity{

    private final String firstName;
    private final String lastName;
    private final PhoneNumber contactNumber;
    private final String address;

    public PersonEntity(String firstName, String lastName, String address,  PhoneNumber contactNumber) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.contactNumber = contactNumber;
        this.address = address;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    @Override
    public PhoneNumber getContactNumber() {
        return contactNumber;
    }

    @Override
    public String getAddress() {
        return address;
    }

    @Override
    public String description() {
        return toString();
    }

    @Override
    public String toString() {
        return "PersonEntity{" +
                "firstName='" + firstName + '\'' +
                ", lastName='" + lastName + '\'' +
                ", contactNumber=" + contactNumber +
                ", address='" + address + '\'' +
                '}';
    }
}
