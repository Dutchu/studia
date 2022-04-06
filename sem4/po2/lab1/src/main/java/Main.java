import com.google.common.collect.Lists;
import org.checkerframework.checker.fenum.qual.SwingBoxOrientation;

import java.math.BigDecimal;
import java.math.MathContext;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {

        /*
        Napisz program rozwiązujący równanie kwadratowe ax2 + bx + c = 0. Współczynniki a, b, c
        przekazywane są z linii poleceń. Uwzględnij w programie pomyłkę użytkownika polegającą na przekazaniu do programu nieprawidłowej liczby parametrów.
        Wskazówka: do konwersji parametrów skorzystaj z funkcji parseDouble w klasie Double. Przed użyciem tej funkcji zapoznaj się z jej specyfikacją.
        Realizację zadania rozpocznij od napisania programu wczytującego parametry wywołania programu i konwertującego je do typu double.
        */


        List<String> argsList = Arrays.stream(args).toList();

        System.out.println("Program arguments: " + argsList);

        BigDecimal a = BigDecimal.ZERO;
        BigDecimal b = BigDecimal.ZERO;
        BigDecimal c = BigDecimal.ZERO;

        try {
            a = new BigDecimal(argsList.get(0));
            b = new BigDecimal(argsList.get(1));
            c = new BigDecimal(argsList.get(2));
        } catch (NumberFormatException | ArrayIndexOutOfBoundsException e) {
            System.err.println(e.getMessage());
        }


        DeltaSolver deltaSolver = new DeltaSolver(a, b, c);

        System.out.println("Delta: " + deltaSolver.getDelta());

        /***
         * Usage of "Factory" Design pattern
         */

        QESolverFactory qeSolverFactory = new QESolverFactory();

        List<BigDecimal> solutions = qeSolverFactory.calcDelta(deltaSolver).solve();

        if (solutions == null) {
            System.out.println("No solutions");
        } else {
            System.out.println("Quadratic equation solutions: " + solutions);
        }


        /***
         * Usage of "Strategy" Design pattern
         */

        System.out.println("Usage of \"Strategy\" Design pattern");

        List<Discounter> discounters = Lists.newArrayList(
                amount -> amount.multiply(BigDecimal.valueOf(0.9)),
                amount -> amount.multiply(BigDecimal.valueOf(0.8)),
                amount -> amount.multiply(BigDecimal.valueOf(0.5))
        );

        Discounter combinedDiscounter = discounters
                .stream()
                .reduce(v -> v, Discounter::combine);

        System.out.println(a);
        System.out.println(combinedDiscounter.apply(a));


    }
}
