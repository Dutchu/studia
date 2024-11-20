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

    @Override
    public void start(Stage primaryStage) {

        WatekCzytajacy producer1 = new WatekCzytajacy("plik1.txt");
        WatekCzytajacy producer2 = new WatekCzytajacy("plik2.txt");
        WatekCzytajacy producer3 = new WatekCzytajacy("plik3.txt");
        
        SharedBuffer.addProducerToList(producer1);
        SharedBuffer.addProducerToList(producer3);
        SharedBuffer.addProducerToList(producer2);
        SharedBuffer.addProducerToList(producer2);
        SharedBuffer.addProducerToList(producer1);
        SharedBuffer.addProducerToList(producer3);
        SharedBuffer.addProducerToList(producer2);
        SharedBuffer.addProducerToList(producer3);
        SharedBuffer.addProducerToList(producer3);
        
        new Thread(producer1).start();
        new Thread(producer2).start();
        new Thread(producer3).start();
        
        WatekPiszacy consumer = new WatekPiszacy();
        new Thread(consumer).start();
    }
}