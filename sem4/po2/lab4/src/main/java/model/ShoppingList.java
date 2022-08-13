package model;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public final class ShoppingList {

    private static ShoppingList INSTANCE;
    private String name;
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
    private ShoppingList(){};

    public static ShoppingList getInstance() {
        if(INSTANCE == null) {
            INSTANCE = new ShoppingList();
        }

        return INSTANCE;
    }

    public void setShoppingList(List<ShoppingCategory> shoppingCategories, String name) {
        this.categories = shoppingCategories;
        this.name = name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setCategories(List<ShoppingCategory> categories) {
        this.categories = categories;
    }

    public List<ShoppingCategory> getCategories() {
        return categories;
    }

    public void addCategories(ShoppingCategory category) {
        if ( categories == null ) categories = new ArrayList<>();
        this.categories.add(category);
    }

    public void addShoppingItem(ShoppingCategory category, ShoppingItem item) {

        category.addItem(item);
        categories.add(category);

    }

    public void removeAll () {
        this.categories =  new ArrayList<>();
    }

    public void removeShoppingItem(ShoppingCategory category, ShoppingItem item) {
        List<ShoppingCategory> matchingList = this.categories.stream()
                .filter(c -> category.getCategoryName().equals(c.getCategoryName())).toList()
        ;
        matchingList.forEach(e -> e.removeItem(item));
    }

    @Override
    public String toString() {
        if (this.categories.size() == 0) {
            return this.name + "";
        }

        return categories.stream()
                .map(e -> e.getCategoryName() + '\n' + e.getItems().stream()
                        .map(i -> '\t' + i.toString())
                        .collect(Collectors.joining("\n")))
                .collect(Collectors.joining("\n"));
    }
}
