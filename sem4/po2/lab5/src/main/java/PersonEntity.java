public class PersonEntity extends Entity{

    private final String FIRST_NAME;
    private final String LAST_NAME;
    private String address;
    private PhoneNumber contactNumber;

    public PersonEntity(String first_name, String last_name) {
        FIRST_NAME = first_name;
        LAST_NAME = last_name;
    }

    @Override
    void description() {

    }
}
