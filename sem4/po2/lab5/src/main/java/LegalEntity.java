public class LegalEntity extends Entity{

    private final String name;
    private final PhoneNumber contactNumber;
    private final String address;


    public LegalEntity(String name, String address, PhoneNumber contactNumber) {
        this.name = name;
        this.contactNumber = contactNumber;
        this.address = address;
    }

    public String getName() {
        return name;
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
        return "LegalEntity{" +
                "name='" + name + '\'' +
                ", contactNumber=" + contactNumber +
                ", address='" + address + '\'' +
                '}';
    }
}
