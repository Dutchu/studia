package org.example;

import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

public class WatekCzytajacy implements Runnable {
    private final String fileName;
    private final TextArea textArea;
    private final Stage stage;
    private static final BlockingQueue<String> sharedBuffer = SharedBuffer.getBuffer();

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

    public String getFileName() {
        return fileName;
    }

    @Override
    public void run() {
        Lock lock = SharedBuffer.getLock();
        Condition producerCondition = SharedBuffer.getProducerCondition();
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            System.out.println("[" + fileName + "] Producer thread started.");

            while ((line = reader.readLine()) != null) {
                System.out.println("[" + fileName + "] Read line: " + line);

                lock.lock();
                try {
                    while (!SharedBuffer.isMyTurn(this)) {
                        System.out.println("[" + fileName + "] Waiting for its turn.");
                        producerCondition.await();
                    }
                } finally {
                    lock.unlock();
                }

                sharedBuffer.put(line);
                String finalLine = line;
                Platform.runLater(() -> textArea.appendText(finalLine + "\n"));
                System.out.println("[" + fileName + "] Sent line: " + line);
                Thread.sleep(100);


                SharedBuffer.switchToNextProducer();
            }

            SharedBuffer.producerFinished();
            System.out.println("[" + fileName + "] Producer thread finished.");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
