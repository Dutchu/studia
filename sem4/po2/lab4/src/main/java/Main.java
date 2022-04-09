import fileReader.FileStream;
import fileReader.LineReader;
import shoppingList.ShoppingCategory;
import shoppingList.ShoppingItem;
import shoppingList.ShoppingList;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Main {

    private static final String ABSOLUTE_PATH = "C:\\Users\\Bartek\\Desktop\\studia\\sem4\\po2\\lab4\\src\\main\\resources\\zakupy.txt";
    private static final String FILE_NAME = "zakupy.txt";

    public static void main(String[] args) throws IOException, ClassNotFoundException {

        /***
         * File access
         */
        LineReader lineReader = new LineReader(FILE_NAME);

        ShoppingItem shoppingItem1 = new ShoppingItem();
        shoppingItem1.setItemName("Bannan");
        ShoppingItem shoppingItem2 = new ShoppingItem();
        shoppingItem2.setItemName("Cebula");
        ShoppingItem shoppingItem3 = new ShoppingItem();
        shoppingItem3.setItemName("Pomidor");

        List<ShoppingItem> shoppingItems = new ArrayList<>();
        shoppingItems.add(shoppingItem1);
        shoppingItems.add(shoppingItem2);
        shoppingItems.add(shoppingItem3);

        ShoppingCategory shoppingCategory1 = new ShoppingCategory();
        shoppingCategory1.setCategoryName("spozywcze");
        shoppingCategory1.setItems(shoppingItems);
        ShoppingCategory shoppingCategory2 = new ShoppingCategory();
        shoppingCategory2.setCategoryName("warzywka");
        shoppingCategory2.setItems(shoppingItems);

        List<ShoppingCategory> shoppingCategoryList = new ArrayList<>();

        ShoppingList shoppingList = new ShoppingList();
        shoppingList.setCategories(shoppingCategoryList);
        System.out.println(shoppingList);
        shoppingList.addCategories(shoppingCategory1);
        System.out.println(shoppingList);
        shoppingList.addCategories(shoppingCategory2);
        System.out.println(shoppingList);

        FileStream fileStream = new FileStream();
        fileStream.setFileName(FILE_NAME);

        fileStream.writeFile(shoppingList.toString());



//        System.out.println(lr.readLine());

//        writeShoppingList(sl);
//        ShoppingList deserializedShoppingList = new ShoppingList();
//        deserializedShoppingList = readShoppingList(deserializedShoppingList);
//        System.out.println("Deserialized Object: " + deserializedShoppingList);
//
//        Book book = new Book();
//        book.setBookName("Baeldung");
//        book.setDescription("Java Serialization");
//        book.setCopies(25);

//        serialize(book);
//        Book deserializedBook = deserialize();

//        System.out.println(deserializedBook);
    }
}

//    private static void writeShoppingList(ShoppingList sl) {
//        System.out.println("[MAIN] writeShoppingList() ");
//        try (FileOutputStream file = new FileOutputStream(FILE_NAME); ObjectOutputStream out = new ObjectOutputStream(file)) {
//            sl.writeExternal(out);
//
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    private static ShoppingList readShoppingList(ShoppingList sl) {
//        System.out.println("[MAIN] readShoppingList() ");
//        try (FileInputStream file = new FileInputStream(FILE_NAME); ObjectInputStream in = new ObjectInputStream(file)) {
//            sl.readExternal(in);
//
//        } catch (IOException | ClassNotFoundException e) {
//            e.printStackTrace();
//        }
//
//        return sl;
//    }
//
//    private static ObjectInputStream readObject() throws IOException {
//        FileInputStream file = new FileInputStream(FILE_NAME);
//        return new ObjectInputStream(file);
//    }
//
//    private static Book deserialize() throws IOException, ClassNotFoundException {
//        FileInputStream file = new FileInputStream(FILE_NAME);
//        ObjectInputStream in = new ObjectInputStream(file);
//        return (Book) in.readObject();
//    }
//
//    private static void serialize(Book book) throws IOException {
//        FileOutputStream file = new FileOutputStream(FILE_NAME);
//        ObjectOutputStream out = new ObjectOutputStream(file);
//        out.writeObject(book);
//        out.close();
//        file.close();
//    }
//}
