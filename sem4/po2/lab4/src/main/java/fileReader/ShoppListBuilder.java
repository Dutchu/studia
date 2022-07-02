package fileReader;

import shoppingList.ShoppingCategory;
import shoppingList.ShoppingItem;
import shoppingList.ShoppingList;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class ShoppListBuilder {
    public ShoppingList build(String fileName) {
        System.out.println("[ ShoppListBuilder.build() ]");

        String lines;
        FileStream fileStream = new FileStream(fileName);
        lines = fileStream.readFileString();

        List<String> itemsLinesList = new ArrayList<>();
        List<String> itemsList = new ArrayList<>();
        List<ShoppingItem> itemsObjList = new ArrayList<>();
        List<String> categoriesList = new ArrayList<>();
        List<String> linesList = Stream.of(lines.split("\\r?\\n"))
                .map(String::new).toList();

        categoriesList = linesList.stream()
                .filter(line -> (line.charAt(0) != '\t'))
                .collect(Collectors.toList());

        itemsLinesList = linesList.stream()
                .filter(line -> (line.charAt(0) == '\t'))
                .collect(Collectors.toList());

        itemsList = itemsLinesList.stream()
                .map(line -> line.substring(1))
                .collect(Collectors.toList());

        itemsObjList = itemsList.stream()
                .map(itemName -> new ShoppingItem(itemName))
                .collect(Collectors.toList());

        ShoppingItem tempItem = new ShoppingItem("");
        List<ShoppingItem> tempItems = new ArrayList<>();
        tempItems.add(tempItem);
        ShoppingCategory tempCategory = new ShoppingCategory("", tempItems);
        List<ShoppingCategory> tempCategories = new ArrayList<>();
        tempCategories.add(tempCategory);
        ShoppingList shoppingList = new ShoppingList(tempCategories);

        for (String line : linesList) {
            if (line.charAt(0) != '\t') {
                tempCategory.setCategoryName(line);
                System.out.println("[ ShoppingListBuilder.build() ] Current Category: " + tempCategory.getCategoryName());
            } else {
                System.out.println("[ ShoppingListBuilder.build() ] Current Item: " + tempItem.getItemName());
                tempItem.setItemName(line.trim());
                tempItems.add(tempItem);
            }

            if(tempCategory.getCategoryName().equals(line)) {
                tempCategory.setItems(tempItems);
            }


//            System.out.println(shoppingList);
        }
        shoppingList.addCategories(tempCategory);

//        System.out.println("Items list: " + itemsList);
//        Map<String, List<String>> map = (Map<String, List<String>>) linesList.stream()
//                .filter(line -> (line.charAt(0) != '\t'))
//                .collect(Collectors.groupingBy(ShoppingCategory::getCategoryName));


        System.out.println("Items: " + itemsList);
        System.out.println("Categories: " + categoriesList);

//        List<ShoppingCategory> listOfShoppingCategories = categoriesList.stream()
//                .map(e -> new ShoppingCategory(e, itemsList))
//                .collect(Collectors.toList());

//        List<ShoppingCategory> lisOfItems = itemsList.stream()
//                .map(e -> new ShoppingCategory(e, ))
//                .collect(Collectors.toList());

//        shoppingList = new ShoppingList(listOfShoppingCategories);

        return shoppingList;
    }
}
