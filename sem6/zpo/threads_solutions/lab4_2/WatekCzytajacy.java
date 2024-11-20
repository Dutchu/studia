package org.example;

import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class WatekCzytajacy implements Runnable {
    private String fileName;
    private TextArea textArea;
    private Stage stage;
    private static BlockingQueue<Character> sharedBuffer = SharedBuffer.getBuffer(); // Wspólny bufor dla znaków
    private static final Lock bufferLock = new ReentrantLock(); // Blokada bufora

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
            StringBuilder currentWord = new StringBuilder();

            while ((data = reader.read()) != -1) {
                char character = (char) data;

                if (Character.isWhitespace(character)) {
                    // Zakończenie słowa, przesyłanie znaków słowa do bufora
                    bufferLock.lock(); // Zablokowanie dostępu do bufora
                    try {
                        for (char c : currentWord.toString().toCharArray()) {
                            sharedBuffer.put(c); // dodanie znaku do bufora
                            Platform.runLater(() -> textArea.appendText(String.valueOf(c)));
                            Thread.sleep(100); // Symulacja opóźnienia
                        }

                        // Wysyłanie znaku białego
                        sharedBuffer.put(character);
                        Platform.runLater(() -> textArea.appendText(String.valueOf(character)));
                        Thread.sleep(100); // Symulacja opóźnienia

                    } finally {
                        bufferLock.unlock(); // Odblokowanie dostępu do bufora
                    }
                    currentWord.setLength(0); // Czyszczenie słowa
                } else {
                    // Dodawanie znaków do aktualnego słowa
                    currentWord.append(character);
                }
            }

            // Obsługa ostatniego słowa (jeśli brak końcowego znaku białego)
            if (currentWord.length() > 0) {
                bufferLock.lock(); // Zablokowanie dostępu do bufora
                try {
                    for (char c : currentWord.toString().toCharArray()) {
                        sharedBuffer.put(c);
                        Platform.runLater(() -> textArea.appendText(String.valueOf(c)));
                        Thread.sleep(100); // Symulacja opóźnienia
                    }
                } finally {
                    bufferLock.unlock(); // Odblokowanie dostępu do bufora
                }
            }

            SharedBuffer.producerFinished(); // Zgłaszanie zakończenia producenta

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
