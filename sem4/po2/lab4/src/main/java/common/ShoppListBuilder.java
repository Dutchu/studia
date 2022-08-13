package common;

import model.ShoppingCategory;
import model.ShoppingItem;
import model.ShoppingList;

import java.util.*;
import java.util.stream.Stream;

public class ShoppListBuilder {

    private static ShoppListBuilder INSTANCE;
    private final ShoppingList shoppingList;
    private final String fileName;

    public static ShoppListBuilder getInstance(ShoppingList shoppingList, String fileName) {
        if (INSTANCE == null) {
            INSTANCE = new ShoppListBuilder(shoppingList, fileName);
        }
        return INSTANCE;
    }

    public static ShoppListBuilder getInstance() {
        if (INSTANCE == null) {
            System.err.println("[ShoppListBuilder] Instance not initialized");
        }
        return INSTANCE;
    }


    private ShoppListBuilder(ShoppingList shoppingList, String fileName) {
        this.shoppingList = shoppingList;
        this.fileName = fileName;
    }


    public void build() {
//        System.out.println("[ ShoppListBuilder.build() ]");

        String lines;
        FileStream fileStream = new FileStream(this.fileName);
        lines = fileStream.readFileString();
        List<String> linesList = Stream.of(lines.split("\\r?\\n"))
                .map(String::new).toList();

        /***
         * Nie można budować za każdym razem z pliku od nowa listy, ponieważ algorytm dodaje za każdym razem do istniejącej listy od nowa to co się tam znajduje
         * Obecnie problemem jest jedna linijka [null{ empty }]
         * Albo nadpisywać listę w programie, albo wymyślić jak unikać budowania listy bez pewności co się w niej znajduje
         */
        System.out.println(linesList.size());
        System.out.println(linesList);
        if (linesList.size() == 0) return;

        //TODO
        List<ShoppingItem> tempItems = new ArrayList<>();
        ShoppingItem tempItem = new ShoppingItem("");
        ShoppingCategory tempCategory = new ShoppingCategory("", tempItems);

        String categoryName = "";
        String itemName;
        for (String line : linesList) {
//            System.out.println("[ShopListBuilder] Current line: " + line + "|");
            if (!line.startsWith("\t")) {

                if (!categoryName.isEmpty()) {

                    if(shoppingList.getCategories() == null) {
                        shoppingList.setCategories(new ArrayList<>());
                    }

                    tempCategory = new ShoppingCategory(categoryName, tempItems);
                    shoppingList.addCategories(tempCategory);
                    tempItems = new ArrayList<>();
                }

                categoryName = line.trim();
//                System.out.println("[ShopListBuilder] Current category: " + categoryName);


            } else {
                itemName = line.trim();
                tempItem = new ShoppingItem(itemName);
                tempItems.add(tempItem);
            }
        }
        tempCategory = new ShoppingCategory(categoryName, tempItems);
        shoppingList.addCategories(tempCategory);
        //TODO END
    }

}

/***
 *         ShoppingItem tempItem = null;
 *         List<ShoppingItem> tempItems = new ArrayList<>();
 *         ShoppingCategory tempCategory = null;
 *         ShoppingList shoppingList = new ShoppingList();
 *         String categoryName = "";
 *         String itemName;
 *         for (String line : linesList) {
 *             System.out.println("[ShopListBuilder] Current line: " + line + "|");
 *             if (!line.startsWith("\t")) {
 *
 *                 if( !categoryName.isEmpty() ) {
 *                     tempCategory = new ShoppingCategory(categoryName, tempItems);
 *                     shoppingList.addCategories(tempCategory);
 *                     tempItems = new ArrayList<>();
 *                 }
 *
 *                 categoryName = line.trim();
 *                 System.out.println("[ShopListBuilder] Current category: " + categoryName);
 *
 *
 *             } else {
 *                 itemName = line.trim();
 *                 tempItem = new ShoppingItem(itemName);
 *                 tempItems.add(tempItem);
 *             }
 *         }
 *         tempCategory = new ShoppingCategory(categoryName, tempItems);
 *         shoppingList.addCategories(tempCategory);
 */
