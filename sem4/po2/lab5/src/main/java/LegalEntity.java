public class LegalEntity extends Entity{

    private final String NAME;
    private String address;
    private PhoneNumber contactNumber;

    public LegalEntity(String name) {
        NAME = name;
    }

    @Override
    void description() {

    }
}
