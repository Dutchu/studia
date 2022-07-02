package shoppingList;

import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.stream.Collectors;

public class ShoppingList {

    private List<ShoppingCategory> categories;

//    @Override
//    public void writeExternal(ObjectOutput out) throws IOException {
//        System.out.println("[shoppingList.ShoppingList] writeExternal() ");
//        out.writeUTF(categories);
//    }

//    @Override
//    public void readExternal(ObjectInput in) throws IOException, ClassNotFoundException {
//        System.out.println("[shoppingList.ShoppingList] readExternal() ");
//        this.categories = (String) in.readUTF();
//    }

    public ShoppingList(List<ShoppingCategory> categories){
        this.categories = categories;
    }

    public List<ShoppingCategory> getCategories() {
        return categories;
    }

    public void setCategories(List<ShoppingCategory> categories) {
        this.categories = categories;
    }

    public void addCategories(ShoppingCategory categories) {
        this.categories.add(categories);
    }

    @Override
    public String toString() {
        return categories.stream()
                .map(e -> e.getCategoryName() + '\n' + e.getItems().stream()
                        .map(i -> '\t' + i.toString())
                        .collect(Collectors.joining("\n")))
                .collect(Collectors.joining("\n"));
    }
}
