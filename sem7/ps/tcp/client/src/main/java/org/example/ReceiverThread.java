package org.example;

import java.io.IOException;
import java.io.InputStream;

public class ReceiverThread implements Runnable {
    InputStream in;

    ReceiverThread(InputStream in) {
        this.in = in;
    }

    @Override
    public void run() {
        byte[] buffer = new byte[1024];
        int bytesRead;
        int totalBytesReceived = 0;

        try {
            while ((bytesRead = in.read(buffer)) != -1) {
                totalBytesReceived += bytesRead;
                String receivedText = new String(buffer, 0, bytesRead);
                System.out.println("[Odebrano " + bytesRead + " B, łącznie: "
                        + totalBytesReceived + " B] -> " + receivedText);
            }
            // Jeśli read() zwróci -1, serwer zamknął gniazdo
            System.out.println("Serwer zamknął połączenie. Kończę działanie klienta...");
            System.exit(0);
        } catch (IOException e) {
            // Jeśli wystąpi IOException, np. zerwanie połączenia
            System.out.println("Połączenie z serwerem zostało przerwane: " + e.getMessage());
            System.exit(0);
        }
    }
}
