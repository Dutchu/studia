package shoppingList;

import java.util.List;
import java.util.Objects;

public class ShoppingCategory {

    private String categoryName;
    private List<ShoppingItem> items;

    public String getCategoryName() {
        return categoryName;
    }

    public List<ShoppingItem> getItems() {
        return items;
    }

    public void setCategoryName(String categoryName) {
        this.categoryName = categoryName;
    }

    public void setItems(List<ShoppingItem> items) {
        this.items = items;
    }


    @Override
    public String toString() {
        return "ShoppingCategory{" +
                "categoryName='" + categoryName + '\'' +
                ", items=" + items +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ShoppingCategory that = (ShoppingCategory) o;
        return Objects.equals(categoryName, that.categoryName) && Objects.equals(items, that.items);
    }

    @Override
    public int hashCode() {
        return Objects.hash(categoryName, items);
    }
}
