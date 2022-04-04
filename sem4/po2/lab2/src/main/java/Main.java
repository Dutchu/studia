import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

import static java.lang.System.out;

public class Main {
    public static void main(String[] args) {
        // Using Scanner for Getting Input from User
        Scanner in = new Scanner(System.in);

        out.println("Gib me text: ");
        String userText = in.nextLine();
        out.println("You entered string " + userText);

        List<Character> userTextList = new ArrayList<>();

        for (char ch : userText.toCharArray()) {
            userTextList.add(ch);
        }

        int listSize = userTextList.size();
        out.println("Your input size: " + listSize);

        out.println("Your input: ");
        userTextList.forEach(out::println);

        out.println("Gib me lower boundary: ");
        int low = 0;
        boolean wrongInput = true;
        while (wrongInput) {
            try {
                low = in.nextInt();
                wrongInput = false;
            } catch (InputMismatchException e) {
                in.nextLine();
                System.err.println("[InputMismatchException] Wrong input! Input only integer numbers please.");
            }

            if (low != 0) {
                out.println("You entered integer " + low);
            }

            if (low > listSize || low < 0) {
                out.println("Wrong input. Text size is different.");
                wrongInput = true;
            }


        }


        out.println("Gib me upper boundary: ");
        int high = 0;
        wrongInput = true;
        List<Character> subList = new ArrayList<>();
        while (wrongInput) {
            try {
                high = in.nextInt();
                wrongInput = false;
            } catch (InputMismatchException e) {
                in.nextLine();
                System.err.println("[InputMismatchException] Wrong input! Input only integer numbers please.");
            }

            if (high != 0) {
                out.println("You entered integer " + high);
            }

            if (high > listSize || high < 0) {
                out.println("Wrong input. Text size is different.");
                wrongInput = true;
            }

            try {
                subList = userTextList.subList(low, high);
            } catch (IllegalArgumentException | IndexOutOfBoundsException e) {
                wrongInput = true;
                System.err.println(e + ". Wrong input!");
            }

        }

        out.print("Your input: ");
        subList.forEach(out::print);

        System.exit(0);
    }
}