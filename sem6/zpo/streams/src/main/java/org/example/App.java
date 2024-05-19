package org.example;

import java.io.*;
import java.nio.CharBuffer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.stream.Stream;

/**
 * Hello world!
 */
public class App {
    private static final String FILE_NAME_INPUT = "english.200MB.txt";
    private static final String FILE_NAME_OUTPUT = "lol.txt";

    //write a static method to read file with
    public static void main(String[] args) {
        processFile(FILE_NAME_INPUT, FILE_NAME_OUTPUT);
    }

    //mierzenie ilości zużywanej pamięci przez program
    //testy sprawdzające zużycie pamięci w czytaniu pliku
    //-Xmx20M
    //Ilość słów n dzielone przez 2. 29M /100 =>  29_500, wartość k=100 buffor na 100 słów. Dlaczego buffor na 100 słó to czmeu jest ich 6. Trzeba dać wartość większą od ilości (częstotliwość występowania) słó któe chcemy znaleźć
    // jeżeli po zmniejszeniu będzie 0, to wylatuje i zwalnia miejsce w słowniku. 100 słów, ale nie koniecznie wsytępujących tyle co N/100 najczęstrrzych słów.


    private static Stream<String> processFile(String fileName, String outputFileName) {
        Stream<String> resultingStream = null;
        Path path = Paths.get(fileName);
        try (Stream<String> lines = Files.lines(path)) {
            resultingStream = lines
                    .map(String::toLowerCase)
                    .map(String::trim)
                    .map(e -> e.replaceAll("[^a-z]+", " "));
            bufferedWriteFile(outputFileName, resultingStream);
        } catch (IOException e) {
            throw new RuntimeException(e.getMessage());
        }
        return resultingStream;
    }

    private static void bufferedWriteFile(String fileName, Stream<String> stringStream) {

        BufferedWriter writer = null;
        try {

            writer = new BufferedWriter(new FileWriter(fileName));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        BufferedWriter finalWriter = writer;
        stringStream.forEach(line -> {
            try {
                finalWriter.write(line);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }});

        try {
            writer.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

//    wszystkie litery zamieniamy na małe
//    usuwamy wszystko co nie jest literą (czyli cyfry, znaki specjalne, przestankowe, apostrofy cudzysłowy, itp)
//    będą nas interesować wyłącznie słowa o długości co najmniej 3 liter.
}
