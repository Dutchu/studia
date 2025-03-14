package org.example;

import java.io.IOException;
import java.net.ServerSocket;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicInteger;

public class ThreadedEchoServer {

    private static final int MAX_CONNECTIONS = 3;

    private static final AtomicInteger activeConnections = new AtomicInteger(0);

    private static final AtomicInteger clientCounter = new AtomicInteger(0);

    public static void main(String[] args) {
        Scanner console = new Scanner(System.in);

        System.out.print("Podaj port serwera [domyślnie 7]: ");
        String portStr = console.nextLine().trim();
        int port = 7;
        if (!portStr.isEmpty()) {
            try {
                port = Integer.parseInt(portStr);
            } catch (NumberFormatException e) {
                System.err.println("Niepoprawny numer portu. Używam domyślnego (7).");
            }
        }

        ServerSocket serverSocket;
        try {

            serverSocket = new ServerSocket(port);
            System.out.println("Serwer ECHO (wielowątkowy) nasłuchuje na porcie: " + port);
            System.out.println("Maksymalna liczba jednoczesnych połączeń: " + MAX_CONNECTIONS);
        } catch (IOException e) {
            System.err.println("Błąd przy tworzeniu gniazda serwera: " + e.getMessage());
            return;
        }

        ListenThread listenThread = new ListenThread(serverSocket);
        listenThread.start();


        System.out.println("Wpisz 'exit' aby zamknąć serwer:");
        while (true) {
            String line = console.nextLine();
            if (line.equalsIgnoreCase("exit")) {
                System.out.println("Zamykanie serwera...");

                listenThread.interrupt();
                try {
                    serverSocket.close();
                } catch (IOException e) {
                    System.err.println("Błąd przy zamykaniu ServerSocket: " + e.getMessage());
                }
                break;
            }
        }

        System.out.println("Serwer został zamknięty.");
    }

    public static int getActiveConnections() {
        return activeConnections.get();
    }

    public static int incrementActiveConnections() {
        return activeConnections.incrementAndGet();
    }

    public static int decrementActiveConnections() {
        return activeConnections.decrementAndGet();
    }

    public static int getAndIncrementClientCounter() {
        return clientCounter.incrementAndGet();
    }

    public static int getMaxConnections() {
        return MAX_CONNECTIONS;
    }
}