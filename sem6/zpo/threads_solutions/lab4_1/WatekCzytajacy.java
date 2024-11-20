package org.example;

import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.concurrent.BlockingQueue;

public class WatekCzytajacy implements Runnable {
    private String fileName;
    private TextArea textArea;
    private Stage stage;
    private static BlockingQueue<Character> sharedBuffer = SharedBuffer.getBuffer(); // Wspólny bufor

    public WatekCzytajacy(String fileName) {
        this.fileName = fileName;
        this.textArea = new TextArea();
        this.stage = new Stage();
        Platform.runLater(() -> {
            stage.setTitle(fileName);
            stage.setScene(new Scene(textArea, 400, 300));
            stage.show();
        });
    }

    @Override
    public void run() {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            int data;
            while ((data = reader.read()) != -1) {
                char character = (char) data;

                // Aktualizacja UI musi być wykonana na Platform.runLater
                Platform.runLater(() -> textArea.appendText(String.valueOf(character)));

                // Umieszczanie znaku w buforze współdzielonym
                sharedBuffer.put(character);

                // Symulacja opóźnienia
                Thread.sleep(100);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
