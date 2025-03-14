package org.example;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class EchoServer {
    public static void main(String[] args) {
        Scanner console = new Scanner(System.in);

        // 1. Wczytanie portu (domyślnie 7)
        System.out.print("Podaj port serwera [domyślnie 7]: ");
        String portStr = console.nextLine().trim();
        int port = 7;  // port domyślny
        if (!portStr.isEmpty()) {
            try {
                port = Integer.parseInt(portStr);
            } catch (NumberFormatException e) {
                System.err.println("Niepoprawny numer portu. Używam domyślnego (7).");
            }
        }

        // 2. Próba utworzenia gniazda serwera
        //    ServerSocket bez podania adresu IP nasłuchuje na wszystkich interfejsach (0.0.0.0).
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(port);
            System.out.println("Serwer ECHO nasłuchuje na porcie " + port + " ...");
        } catch (IOException e) {
            System.err.println("Błąd przy tworzeniu ServerSocket: " + e.getMessage());
            System.exit(1);
        }

        // Licznik klientów - każdy podłączający się klient dostaje kolejny numer #.
        int clientCounter = 0;

        // 3. Pętla nasłuchiwania (iteracyjna)
        //    W każdej iteracji akceptujemy JEDNO połączenie i obsługujemy je w tym samym wątku.
        //    Po zakończeniu (lub zerwaniu) połączenia przechodzimy do akceptacji kolejnego klienta.
        while (true) {
            try (Socket clientSocket = serverSocket.accept()) {
                clientCounter++;

                // Pobieramy informacje o kliencie
                InetSocketAddress remoteAddress =
                        (InetSocketAddress) clientSocket.getRemoteSocketAddress();
                String clientIP = remoteAddress.getAddress().getHostAddress();
                int clientPort = remoteAddress.getPort();

                // Logujemy na konsoli nawiązanie połączenia
                System.out.println("[" + clientCounter + "] Połączono z klientem: "
                        + clientIP + ":" + clientPort);

                // 4. Odbieranie i odsyłanie danych (ECHO)
                try (InputStream in = clientSocket.getInputStream();
                     OutputStream out = clientSocket.getOutputStream()) {

                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = in.read(buffer)) != -1) {
                        // Odczytane bajty -> wyświetlamy informację
                        String receivedText = new String(buffer, 0, bytesRead);
                        System.out.println("[" + clientCounter + "] Otrzymano " + bytesRead
                                + " B: \"" + receivedText + "\"");

                        // Odsyłamy wierną kopię odebranych danych (dokładnie tyle bajtów)
                        out.write(buffer, 0, bytesRead);
                        out.flush();
                    }
                } catch (IOException e) {
                    // Obsługa błędów w trakcie komunikacji
                    System.out.println("[" + clientCounter + "] Błąd komunikacji: " + e.getMessage());
                }

                // Po wyjściu z pętli while(...) gniazdo klienta zostaje zamknięte
                System.out.println("[" + clientCounter + "] Rozłączono klienta: "
                        + clientIP + ":" + clientPort);

            } catch (IOException e) {
                // Błąd przy accept() lub przy pracy z gniazdem
                System.err.println("Błąd przy obsłudze klienta: " + e.getMessage());
            }
        }
        // serverSocket.close() nigdy się tu nie wywoła w pętli nieskończonej;
        // aby zatrzymać serwer, przerwij działanie aplikacji (np. Ctrl + C).
    }
}
