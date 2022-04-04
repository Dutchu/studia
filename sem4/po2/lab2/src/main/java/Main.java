import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.List;
import java.util.Scanner;

import static java.lang.System.out;

public class Main {
    public static void main(String args[]) {
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
        int low = in.nextInt();
        out.println("You entered integer " + low);

        if (low < 0 || low > listSize) {
            out.println("Wrong input");
            System.exit(1);
        }

        out.println("Gib me upper boundary: ");
        int high = in.nextInt();

        boolean inputNotNull = true;
        while (inputNotNull) {
            try {
                high = in.nextInt();

                System.out.printf("The number %d is power of 2: %b\n", number, isPowerOfTwo(number));
                if (high == 0) {
                    inputNotNull = false;
                }
            }
            catch (InputMismatchException e) {
                System.err.println("Wrong input! Input only integer numbers please...");
                in.nextLine();
            }
            out.println("You entered integer " + high);

            if (high > listSize || high < 0) {
                out.println("Wrong input");
                System.exit(1);
            }

            List<Character> subList = userTextList.subList(low, high);

            subList.forEach(out::println);
        }
    }
