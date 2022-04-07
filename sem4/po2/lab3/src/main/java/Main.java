import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;


public class Main {

    static final int AVAILABLE_TRIES = 3;
    static final Scanner sc = new Scanner(System.in);
    static final Random random = new Random();

    /***
     * Napisz program losujący liczbę z zakresu 0-N. Limit zakresu N przekazywany jest z linii poleceń.
     * Program pyta użytkownika, jaka jest wylosowana liczba. Jeżeli użytkownik nie zgadł,
     * dowiaduje się czy wylosowana liczba jest większa czy mniejsza od podanej.
     * Jeżeli zgadł, dowiaduje się ile wykonał prób i jest pytany czy chce kontynuować grę.
     * Uwzględnij w programie wszelkie możliwe pomyłki użytkownika w przekazaniu parametru do programu.
     */
    public static void main(String[] args) {
        System.out.println("Zabawna Giereczka");

        int menuOption = -1;
//        Scanner sc = new Scanner(System.in);
//        Random random = new Random();

        boolean gameLoop = true;
        while (gameLoop) {

            menuOption = menuPrompt();

            switch (menuOption) {

                case 1 -> gameLoop = false;

                case 2 -> roundLoop();

                default -> System.out.println("Something's fucky");
            }
        }

        System.out.println("Bye, Looser!");
    }

    private static void roundLoop() {
        int randomNumber = 0;
        int triesLeft = AVAILABLE_TRIES;
        int roundCounter = 0;
        int userNumber = 0;
        int userBoundary = 0;
        boolean continueRound = true;

        randomNumber = nextIntRandom();
        if (randomNumber < 0){
            return;
        }
        System.out.println("Random number: " + randomNumber);

        while (continueRound) {
            System.out.println("I can dance all day, I can dance all day.\nTry hit me, try hit me.");
            System.out.println("Tries left: " + triesLeft + " [retire: 0]");

            userNumber = scanIntegerInput();

            if (userNumber == 0) {
                triesLeft = 0;
                break;
            }

            if (userNumber == randomNumber) {
                System.out.println("\033[0;32m" + "Gatch'ya bitsh!" + "\033[0m");
                continueRound = false;
            } else {
                triesLeft--;
            }

            if (triesLeft == 0) {
                System.out.println("\033[0;31m" + "You succ" + "\033[0m");
                continueRound = false;
            }

            roundCounter++;
        }

        System.out.println("Your score: " + triesLeft + "/" + AVAILABLE_TRIES);

    }

    private static int nextIntRandom() {
        System.out.println("Gib me boundary polx");
        int randomNumber = -1;
        boolean error = true;
        int userBoundary = -1;

        while (error) {
            userBoundary = scanIntegerInput();
            if (userBoundary == -1) {
                break;
            }
            try {
                randomNumber = random.nextInt(userBoundary) + 1;
                error = false;
            } catch (IllegalArgumentException e) {
                System.err.println(e.getMessage() + " You gave me a not positive boundary!");
            }
        }

        return randomNumber;
    }

    private static int menuPrompt() {
        System.out.println("1. Exit\n2. Play");
        System.out.println("Gib me option plox:");

        int userInput;
        userInput = scanIntegerInput();

        if (userInput != 1 && userInput != 2) {
            System.out.println("Wrong option");
            return -1;
        }

        return userInput;
    }

    private static int scanIntegerInput() {
        int userInput = -1;
        boolean error = true;
        while (error) {
            System.out.print("Gib me int plox:\n> ");
            try {
                userInput = sc.nextInt();
                error = false;
            } catch (InputMismatchException e) {
                System.err.println("That's not an int, you goofball ");
                sc.nextLine();
            }
        }
        return userInput;
    }
}
