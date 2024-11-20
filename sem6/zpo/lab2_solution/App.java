package org.example;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Stream;


public class App {
    private static final String FILE_NAME_INPUT = "english.200MB.txt";
    static int k = 100;

    public static void main(String[] args) {
        Function<String, String> normalize = line -> line.toLowerCase().replaceAll("[^a-z]", " ");
        Predicate<String> filterWords = word -> word.length() >= 3;
        Map<String, Integer> D1 = new HashMap<>();
        Map<String, Integer> D2 = new HashMap<>();

        Path path = Paths.get(FILE_NAME_INPUT);
        try (Stream<String> lines = Files.lines(path)) {
            lines.flatMap(line -> Arrays.stream(normalize.apply(line).split("\\s+")))
                    .filter(filterWords)
                    .forEach(word -> processWord(D1, word, k));
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }

        try (Stream<String> lines = Files.lines(path)) {
            lines.flatMap(line -> Arrays.stream(normalize.apply(line).split("\\s+")))
                    .filter(filterWords)
                    .filter(D1::containsKey)
                    .forEach(word -> D2.put(word, D2.getOrDefault(word, 0) + 1));
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }

        int n = D2.values().stream().mapToInt(Integer::intValue).sum();
        int threshold = n / k;

        D2.entrySet().removeIf(entry -> entry.getValue() <= threshold);
        printResults(D2);
    }

    private static void processWord(Map<String, Integer> D1, String word, int k) {
        if (D1.containsKey(word)) {
            D1.put(word, D1.get(word) + 1);
        } else if (D1.size() < k - 1) {
            D1.put(word, 1);
        } else {
            D1.replaceAll((key, value) -> value - 1);
            D1.entrySet().removeIf(entry -> entry.getValue() == 0);
        }
    }

    private static void printResults(Map<String, Integer> D2) {
        System.out.println("the: " + D2.getOrDefault("the", 0));
        System.out.println("and: " + D2.getOrDefault("and", 0));
        System.out.println("that: " + D2.getOrDefault("that", 0));
        System.out.println("was: " + D2.getOrDefault("was", 0));
        System.out.println("his: " + D2.getOrDefault("his", 0));
        System.out.println("with: " + D2.getOrDefault("with", 0));
    }
}
