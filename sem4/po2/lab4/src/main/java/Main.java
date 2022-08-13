import common.FileStream;
import common.ShoppListBuilder;
import managers.ListManager;
import managers.MenuOptions;
import model.ShoppingCategory;
import model.ShoppingItem;
import model.ShoppingList;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.stream.Collectors;

import static managers.MenuOptions.*;



public class Main {

    private static final String ABSOLUTE_PATH = "C:\\Users\\Bartek\\Desktop\\studia\\sem4\\po2\\lab4\\src\\main\\resources\\zakupy.txt";
    private static final String FILE_NAME = "zakupy.txt";
    private static final Scanner SC = new Scanner(System.in);
    private static final ShoppingList SHOPPING_LIST = ShoppingList.getInstance();
    private static final ShoppListBuilder LIST_BUILDER = ShoppListBuilder.getInstance(SHOPPING_LIST, FILE_NAME);
    private static final FileStream FILE_STREAM = new FileStream(FILE_NAME);
    private static final ListManager LIST_MANAGER = ListManager.getInstance(SHOPPING_LIST, LIST_BUILDER, FILE_STREAM);
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";


    public static void main(String[] args) throws IOException, ClassNotFoundException {


//        System.out.println("Give your list a name : ");
//        SHOPPING_LIST.setName( SC.nextLine() );

        LIST_MANAGER.build();

        Integer input;
        while (true) {


            System.out.println(ANSI_BLUE + "Pick option:\n" +
                    "                 1 -> SAVE\n" +
                    "                 2 -> DISPLAY\n" +
                    "                 3 -> UPDATE\n" +
                    "                 4 -> DELETE\n" +
                    "                 5 -> DELETE_ALL\n" +
                    "                 6 -> EXIT\n" +
                    "           default -> EXIT" + ANSI_RESET);
            input = SC.nextInt();
            SC.nextLine();

            var result = switch (input) {
                case 1 -> SAVE;
                case 2 -> PRINT;
                case 3 -> UPDATE;
                case 4 -> DELETE;
                case 5 -> DELETE_ALL;
                case 6 -> EXIT;
                default -> EXIT;
            };
            if (result == EXIT) {
                break;
            }

            int if_success = execute(result);
            switch (if_success) {
                case 1 -> System.out.println(ANSI_GREEN + "Success" + ANSI_RESET);
                case 2 -> System.out.println(ANSI_RED + "failure" + ANSI_RESET);
                default -> System.out.println("Undefined behaviour");
            };

        }

//        System.out.println("[MAIN] resulting list : \n" + SHOPPING_LIST);

    }

    private static int execute(MenuOptions option) {
        return switch (option) {
            case SAVE -> save();
            case PRINT -> print();
            case UPDATE -> update();
            case DELETE -> delete();
            case DELETE_ALL -> deleteAll();
            case EXIT -> 0;
        };
    }

    private static int deleteAll() {
        return LIST_MANAGER.deleteAll();
    }

    private static int delete() {
        String category;
        String item;
        ShoppingCategory shoppingCategory;
        ShoppingItem shoppingItem;
        System.out.println(ANSI_BLUE + "Give me category of an item to delete : " + ANSI_RESET);
        category = SC.nextLine();
        System.out.println(ANSI_BLUE + "Give me an item to delete : " + ANSI_RESET);
        item = SC.nextLine();

        shoppingCategory = new ShoppingCategory(category, new ArrayList<>());
        shoppingItem = new ShoppingItem(item);

        return LIST_MANAGER.delete(shoppingCategory, shoppingItem);
    }

    private static int update() {
        String line;
        String category;
        List<String> items = new ArrayList<>();
        List<ShoppingItem> shoppingItems = new ArrayList<>();
        ShoppingCategory shoppingCategory;
        System.out.println(ANSI_BLUE + "Give me category of an item : " + ANSI_RESET);
        category = SC.nextLine();
        System.out.println("[Main] category : " + category);
        System.out.println(ANSI_BLUE + "Give me items : (Hit 'enter' to end)" + ANSI_RESET);

        while (true) {
            line = SC.nextLine();
            if ("".equals(line)) break;
            items.add( line );
            System.out.println("[Main] items : " + items);
            //EAT new line character

        }
        shoppingItems = items.stream()
                .map(ShoppingItem::new)
                .collect(Collectors.toList());

        shoppingCategory = new ShoppingCategory(category, shoppingItems);
        System.out.println("[main] Shopping category to add : " + shoppingCategory);
        return LIST_MANAGER.updateList(shoppingCategory);

    }

    private static int print() {
        return LIST_MANAGER.printShoppingList();
    }

    private static int save() {
        LIST_MANAGER.save();
        return 0;
    }

}

/***
 *         LineReader lineReader = new LineReader(FILE_NAME);
 *
 *         ShoppingItem shoppingItem1 = new ShoppingItem("Bannan");
 *         ShoppingItem shoppingItem2 = new ShoppingItem("Cebula");
 *         ShoppingItem shoppingItem3 = new ShoppingItem("Pomidor");
 *         ShoppingItem shoppingItem4 = new ShoppingItem("Jajka");
 *
 *         ShoppingItem shoppingItem5 = new ShoppingItem("Pilka");
 *         ShoppingItem shoppingItem6 = new ShoppingItem("Koszulki");
 *         ShoppingItem shoppingItem7 = new ShoppingItem("Korki");
 *         ShoppingItem shoppingItem8 = new ShoppingItem("Spodenki");
 *
 *         ShoppingItem shoppingItem9 = new ShoppingItem("Opony");
 *         ShoppingItem shoppingItem10 = new ShoppingItem("Hamulce");
 *         ShoppingItem shoppingItem11 = new ShoppingItem("Wycieraczki");
 *         ShoppingItem shoppingItem12 = new ShoppingItem("Tapicerka");
 *
 *         List<ShoppingItem> shoppingItems1 = new ArrayList<>();
 *         shoppingItems1.add(shoppingItem1);
 *         shoppingItems1.add(shoppingItem2);
 *         shoppingItems1.add(shoppingItem3);
 *         shoppingItems1.add(shoppingItem4);
 *
 *         List<ShoppingItem> shoppingItems2 = new ArrayList<>();
 *         shoppingItems2.add(shoppingItem5);
 *         shoppingItems2.add(shoppingItem6);
 *         shoppingItems2.add(shoppingItem7);
 *         shoppingItems2.add(shoppingItem8);
 *
 *         List<ShoppingItem> shoppingItems3 = new ArrayList<>();
 *         shoppingItems3.add(shoppingItem9);
 *         shoppingItems3.add(shoppingItem10);
 *         shoppingItems3.add(shoppingItem11);
 *         shoppingItems3.add(shoppingItem12);
 *
 *         ShoppingCategory shoppingCategory1 = new ShoppingCategory("spozywcze", shoppingItems1);
 *         ShoppingCategory shoppingCategory2 = new ShoppingCategory("sportowe", shoppingItems2);
 *         ShoppingCategory shoppingCategory3 = new ShoppingCategory("moto", shoppingItems3);
 *
 *
 *         List<ShoppingCategory> shoppingCategoryList = new ArrayList<>();
 *
 *         ShoppingList shoppingList = new ShoppingList(shoppingCategoryList, "MyShoppingList");
 *
 *         System.out.println(shoppingList);
 *         shoppingList.addCategories(shoppingCategory1);
 *         System.out.println(shoppingList);
 *         shoppingList.addCategories(shoppingCategory2);
 *         System.out.println(shoppingList);
 *         shoppingList.addCategories(shoppingCategory3);
 *         System.out.println(shoppingList);
 *
 * //        FileStream fileStream = new FileStream(FILE_NAME);
 * //        fileStream.writeFile(shoppingList.toString());
 *
 * //        FileParser fileParser = new FileParser();
 * //        fileParser.getMessage(FILE_NAME);
 *
 * //        System.out.println("\nFile: " + fileStream.readLineString());
 *
 *         ShoppListBuilder shoppListBuilder = new ShoppListBuilder(shoppingList, FILE_NAME);
 *         shoppListBuilder.build();
 *         System.out.println("[MAIN] \n" + shoppingList);
 *
 *         System.out.println(shoppingList.getCategories());
 *
 *         ShoppingCategory shoppingCategory4 = new ShoppingCategory("Test", new ArrayList<>());
 *         shoppingList.addShoppingItem(shoppingCategory4, shoppingItem12);
 *
 *         System.out.println(shoppingList);
 *
 *         shoppingList.removeShoppingItem(shoppingCategory1, shoppingItem1);
 *
 *         System.out.println(shoppingList);
 *
 *         shoppingList.removeAll();
 *
 *         System.out.println("remove kebab + " + shoppingList);
 */

