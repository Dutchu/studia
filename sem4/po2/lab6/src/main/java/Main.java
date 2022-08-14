import expetions.VectorDifferentLengthException;

import java.io.*;
import java.util.Scanner;

public class Main {
    private final static Scanner SC = new Scanner(System.in);

    public static void main(String[] args) {

        Long input1;
        Long input2;

        while (true) {


            input1 = getaLong("Podaj wektor 1 : ");

            System.out.println("Input 1 = " + input1);

            input2 = getaLong("Podaj wektor 2 : ");

            System.out.println("Input 2 = " + input2);


            try {
                compare(input1, input2);
                break;
            } catch (VectorDifferentLengthException e) {
                System.err.println(e.getMessage() + "\nPodaj liczby o takiej samej dlugosci!");
            }
        }


    }

    private static Long getaLong(String x) {
        long input1;
        System.out.println(x);
        while (!SC.hasNextLong()) {
            SC.next();
        }
        input1 = SC.nextLong();
        return input1;
    }

    private static void compare(Long vector1, Long vector2) {
        String s1 = String.valueOf(vector1);
        String s2 = String.valueOf(vector2);

        if (s1.length() != s2.length()) {
            throw new VectorDifferentLengthException("Dlugosc pierwszego wektora to: " + s1.length() + ", a drugiego to: " + s2.length());
        } else {
            save(vector1 + vector2);
        }

    }

    private static void save(long vector) {
        String sVector = String.valueOf(vector);

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("result.txt"))) {
            writer.write(sVector);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
