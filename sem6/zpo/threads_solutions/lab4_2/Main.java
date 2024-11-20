package org.example;


import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main extends Application {

    static final String FILE_NAME = "example.txt";
    static final int SLEEP_DURATION = 500;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // Uruchamianie wątków producentów
        new Thread(new WatekCzytajacy("plik1.txt")).start();
        new Thread(new WatekCzytajacy("plik2.txt")).start();
        new Thread(new WatekCzytajacy("plik3.txt")).start();

        // Uruchamianie wątku konsumenta
        new Thread(new WatekPiszacy()).start();
    }
}