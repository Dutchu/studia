package org.example;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class EchoClient {
    public static void main(String[] args) {
        Thread thread;
        Scanner console = new Scanner(System.in);

        System.out.print("Podaj adres serwera (np. echo.example.com lub 192.168.0.10): ");
        String host = console.nextLine().trim();

        System.out.print("Podaj port serwera (np. 7 lub 12345): ");
        int port;
        try {
            port = Integer.parseInt(console.nextLine().trim());
        } catch (NumberFormatException e) {
            System.err.println("Nieprawidłowy port. Zamykanie programu...");
            return;
        }

        Socket socket;
        try {
            socket = new Socket(host, port);
            System.out.println("Połączono z " + host + ":" + port);
        } catch (IOException e) {
            System.err.println("Błąd podczas łączenia z serwerem: " + e.getMessage());
            return;
        }

        try (Socket s = socket;
             InputStream in = s.getInputStream();
             OutputStream out = s.getOutputStream()) {
            thread = new Thread(new ReceiverThread(in));
            thread.start();

            System.out.println("STATUS: Połączenie ustanowione");
            System.out.println("Wpisz 'exit' aby zakończyć działanie klienta.\n");

            int totalBytesSent = 0;
            while (true) {
                String line = console.nextLine();
                if (line.equalsIgnoreCase("exit")) {
                    System.out.println("Zakończenie pracy klienta...");
                    break;
                }

                byte[] data = line.getBytes();
                out.write(data);
                out.flush();
                totalBytesSent += data.length;
                System.out.println("[Wysłano " + data.length + " B, łącznie: "
                        + totalBytesSent + " B] -> " + line);
            }

            System.out.println("Zamykam gniazdo...");
        } catch (IOException e) {
            System.err.println("Błąd podczas komunikacji z serwerem: " + e.getMessage());
        }

        System.out.println("STATUS: Połączenie zamknięte");
    }
}
