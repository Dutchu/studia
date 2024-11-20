package org.example;

import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.FileWriter;
import java.util.concurrent.BlockingQueue;

public class WatekPiszacy implements Runnable {
    private final TextArea textArea;
    private final Stage stage;
    private static final BlockingQueue<String> sharedBuffer = SharedBuffer.getBuffer();

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
            System.out.println("[WatekPiszacy] Wątek konsumenta uruchomiony.");

            while (true) {
                String line = sharedBuffer.take();
                System.out.println("[WatekPiszacy] Odebrano linię: " + line);

                Platform.runLater(() -> textArea.appendText(line + "\n"));
                writer.write(line + "\n");
                writer.flush();

                Thread.sleep(100);

                if (SharedBuffer.isAllProducersFinished() && sharedBuffer.isEmpty()) {
                    System.out.println("[WatekPiszacy] Wątek konsumenta zakończony.");
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
