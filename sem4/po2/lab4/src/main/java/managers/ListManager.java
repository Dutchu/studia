package managers;

import common.FileStream;
import common.ShoppListBuilder;
import model.ShoppingCategory;
import model.ShoppingItem;
import model.ShoppingList;

public class ListManager {

    private static ListManager INSTANCE;
    private final ShoppingList shoppingList;
    private final ShoppListBuilder builder;
    private final FileStream fileStream;

    public static ListManager getInstance() {
        if (INSTANCE == null) {
            System.err.println("[ListManager] Instance not initialized");
        }
        return INSTANCE;
    }

    public static ListManager getInstance(ShoppingList shoppingList, ShoppListBuilder builder, FileStream fileStream) {
        if (INSTANCE == null) {
            INSTANCE = new ListManager(shoppingList, builder, fileStream);
        }
        return INSTANCE;
    }

    private ListManager(ShoppingList shoppingList, ShoppListBuilder builder, FileStream fileStream) {
        this.shoppingList = shoppingList;
        this.builder = builder;
        this.fileStream = fileStream;
    }

    public int updateList(ShoppingCategory category) {
        if (category.getCategoryName().equals("")) return 2;

        shoppingList.addCategories(category);
        boolean ifEquals = shoppingList.getCategories().stream()
                .anyMatch(e -> e.getCategoryName().equals(category.getCategoryName()));

        if (ifEquals) return 1;
        return 0;
    }

    public int delete(ShoppingCategory category, ShoppingItem item) {
        if (category == null || item == null) return 0;

        shoppingList.removeShoppingItem(category, item);

        ShoppingCategory firstCategoryFound = shoppingList.getCategories().stream()
                .filter(category::equals)
                .findFirst()
                .orElse(null);

        if (firstCategoryFound == null) return 0;

        boolean anyItemMatch = firstCategoryFound.getItems().stream()
                .anyMatch(e -> item.getItemName().equals(e.getItemName()));

        if (anyItemMatch) return 2;

        return 1;
    }

    public int deleteAll() {
        shoppingList.removeAll();
        if (shoppingList.getCategories().size() == 0) return 1;
        else return 2;

    }

    public int printShoppingList() {
        if (shoppingList.getCategories().size() == 0) return 2;
        System.out.println(shoppingList);
        return 1;
    }

    public ShoppingList getShoppingList() {
        return shoppingList;
    }

    public void build() {
        builder.build();
    }

    public int save() {
        return fileStream.writeFile(shoppingList.toString());
    }
}
