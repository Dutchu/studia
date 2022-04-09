import java.io.*;

public class ShoppingList implements Externalizable {

    private String categories;
    @Serial
    private static final long serialVersionUID = 1L;

    public void setCategories(String categories) {
        this.categories = categories;
    }

    public String getCategories() {
        return this.categories;
    }

    @Override
    public void writeExternal(ObjectOutput out) throws IOException {
        System.out.println("[ShoppingList] writeExternal() ");
        out.writeUTF(categories);
    }

    @Override
    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
        System.out.println("[ShoppingList] readExternal() ");
        this.categories = (String) in.readUTF();
    }

    @Override
    public String toString() {
        System.out.println("[ShoppingList] toString() ");
        return "ShoppingList{" +
                "categories='" + categories + '\'' +
                '}';
    }

}
