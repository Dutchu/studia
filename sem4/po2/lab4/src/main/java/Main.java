import fileReader.FileStream;
import fileReader.FileParser;
import fileReader.LineReader;
import fileReader.ShoppListBuilder;
import shoppingList.ShoppingCategory;
import shoppingList.ShoppingItem;
import shoppingList.ShoppingList;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Main {

    private static final String ABSOLUTE_PATH = "C:\\Users\\Bartek\\Desktop\\studia\\sem4\\po2\\lab4\\src\\main\\resources\\zakupy.txt";
    private static final String FILE_NAME = "zakupy.txt";

    public static void main(String[] args) throws IOException, ClassNotFoundException {

        /***
         * File access
         */
        LineReader lineReader = new LineReader(FILE_NAME);

        ShoppingItem shoppingItem1 = new ShoppingItem("Bannan");
        ShoppingItem shoppingItem2 = new ShoppingItem("Cebula");
        ShoppingItem shoppingItem3 = new ShoppingItem("Pomidor");
        ShoppingItem shoppingItem4 = new ShoppingItem("Jajka");

        ShoppingItem shoppingItem5 = new ShoppingItem("Pilka");
        ShoppingItem shoppingItem6 = new ShoppingItem("Koszulki");
        ShoppingItem shoppingItem7 = new ShoppingItem("Korki");
        ShoppingItem shoppingItem8 = new ShoppingItem("Spodenki");

        ShoppingItem shoppingItem9 = new ShoppingItem("Opony");
        ShoppingItem shoppingItem10 = new ShoppingItem("Hamulce");
        ShoppingItem shoppingItem11 = new ShoppingItem("Wycieraczki");
        ShoppingItem shoppingItem12 = new ShoppingItem("Tapicerka");

        List<ShoppingItem> shoppingItems1 = new ArrayList<>();
        shoppingItems1.add(shoppingItem1);
        shoppingItems1.add(shoppingItem2);
        shoppingItems1.add(shoppingItem3);
        shoppingItems1.add(shoppingItem4);

        List<ShoppingItem> shoppingItems2 = new ArrayList<>();
        shoppingItems2.add(shoppingItem5);
        shoppingItems2.add(shoppingItem6);
        shoppingItems2.add(shoppingItem7);
        shoppingItems2.add(shoppingItem8);

        List<ShoppingItem> shoppingItems3 = new ArrayList<>();
        shoppingItems3.add(shoppingItem9);
        shoppingItems3.add(shoppingItem10);
        shoppingItems3.add(shoppingItem11);
        shoppingItems3.add(shoppingItem12);

        ShoppingCategory shoppingCategory1 = new ShoppingCategory("spozywcze", shoppingItems1);
        ShoppingCategory shoppingCategory2 = new ShoppingCategory("sportowe", shoppingItems2);
        ShoppingCategory shoppingCategory3 = new ShoppingCategory("moto", shoppingItems3);


        List<ShoppingCategory> shoppingCategoryList = new ArrayList<>();

        ShoppingList shoppingList = new ShoppingList(shoppingCategoryList);

        System.out.println(shoppingList);
        shoppingList.addCategories(shoppingCategory1);
        System.out.println(shoppingList);
        shoppingList.addCategories(shoppingCategory2);
        System.out.println(shoppingList);
        shoppingList.addCategories(shoppingCategory3);
        System.out.println(shoppingList);

        FileStream fileStream = new FileStream(FILE_NAME);
        fileStream.writeFile(shoppingList.toString());

        FileParser fileParser = new FileParser();
        fileParser.getMessage(FILE_NAME);

        System.out.println("\nFile: " + fileStream.readLineString());

        ShoppListBuilder shoppListBuilder = new ShoppListBuilder();
        shoppingList = shoppListBuilder.build(FILE_NAME);
        System.out.println("[MAIN] " + shoppingList);


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
