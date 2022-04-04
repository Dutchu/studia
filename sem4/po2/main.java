import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.NoSuchElementException;
import java.util.Scanner;

public class Main {

    public jastatic void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Double> parameters = new ArrayList<>();

        System.out.print("Podaj wspolczynniki a b c oddzielone spacja: ");

        for (int i = 0; i < 3; i++) {
            try {
                parameters.add(scanner.nextDouble());
            } catch (InputMismatchException inputMismatchException) {
                System.out.println("Podaj liczby w formacie double !");
                System.exit(-1);
            } catch (NoSuchElementException noSuchElementException) {
                System.out.println("Podano za malo argumentow");
                System.exit(-1);
            }
        }

        System.out.println("Rozwiazanie dla : a = " + parameters.get(0) + " b = " + parameters.get(1) + " c = " + parameters.get(2));

        double delta = (parameters.get(1) * parameters.get(1)) - 4 * parameters.get(0) * parameters.get(2);
        
        if (delta > 0) {
            System.out.println("x1 = " + (-parameters.get(1) - Math.sqrt(delta))/(2 * parameters.get(0)));
            System.out.println("x2 = " + (-parameters.get(1) + Math.sqrt(delta))/(2 * parameters.get(0)));
        } else if (delta == 0) {
            System.out.println("x = " + (-parameters.get(1)/(2 * parameters.get(0))));
        } else {
            System.out.println("Brak rozwiazan");
        }
    }
}