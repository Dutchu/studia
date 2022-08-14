import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

public class Main {

    public static void main(String[] args) {


        PersonEntity p0 = new PersonEntity("name0", "last0", "xd", new PhoneNumber(48, 720));
        PersonEntity p1 = new PersonEntity("name1", "last1", "xd1", new PhoneNumber(48, 721));
        PersonEntity p2 = new PersonEntity("name2", "last2", "xd2", new PhoneNumber(48, 722));

        LegalEntity l0 = new LegalEntity("company0", "xd", new PhoneNumber(46, 620));
        LegalEntity l1 = new LegalEntity("company1", "xd1", new PhoneNumber(46, 621));
        LegalEntity l2 = new LegalEntity("company2", "xd2", new PhoneNumber(46, 622));

        Map<PhoneNumber, Entity> map = new TreeMap<>();

        map.put(p0.getContactNumber(), p0);
        map.put(p1.getContactNumber(), p0);
        map.put(p2.getContactNumber(), p0);

        map.put(l0.getContactNumber(), l0);
        map.put(l1.getContactNumber(), l1);
        map.put(l2.getContactNumber(), l2);

        map.forEach((k, v) -> System.out.println(k.toString() + " " + v));

        Map<PhoneNumber, Entity> uniqueMap =uniqueAddressMap(map);

        uniqueMap.forEach((k, v) -> System.out.println(
                "UNIQUE " + k.toString() + " " + v));
    }

    private static Map<PhoneNumber, Entity> uniqueAddressMap(Map<PhoneNumber, Entity> entityMap) {

        Map<String, Entity> uniques = new TreeMap<>();
        entityMap.forEach(
                (k, v) -> uniques.put(v.getAddress(), v)
        );

        entityMap.clear();

        uniques.forEach(
                (k, v) -> {
                    entityMap.put(
                            v.getContactNumber(),
                            v
                    );
                }
        );

        return entityMap;

    }
}
