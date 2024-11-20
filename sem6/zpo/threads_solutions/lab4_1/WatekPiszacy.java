package org.example;

import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.concurrent.BlockingQueue;

public class WatekPiszacy implements Runnable {
    private TextArea textArea;
    private Stage stage;
    private static BlockingQueue<Character> sharedBuffer = SharedBuffer.getBuffer(); // Wspólny bufor

    public WatekPiszacy() {
        this.textArea = new TextArea();
        this.stage = new Stage();
        Platform.runLater(() -> {
            stage.setTitle("WatekPiszacy");
            stage.setScene(new Scene(textArea, 400, 300));
            stage.show();
        });
    }

    @Override
    public void run() {
        try (FileWriter writer = new FileWriter("wynik.txt")) {
            while (true) {
                char character = sharedBuffer.take(); // Pobieranie znaku z buforu

                // Aktualizacja UI musi być wykonana na Platform.runLater
                Platform.runLater(() -> textArea.appendText(String.valueOf(character)));

                writer.write(character);
                writer.flush();

                // Symulacja opóźnienia
                Thread.sleep(100);

                // Jeśli warunki zakończenia są spełnione, wątek może zakończyć działanie
                if (SharedBuffer.isAllProducersFinished() && sharedBuffer.isEmpty()) {
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
