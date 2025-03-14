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

        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(port);
            System.out.println("Serwer ECHO nasłuchuje na porcie " + port + " ...");
        } catch (IOException e) {
            System.err.println("Błąd przy tworzeniu ServerSocket: " + e.getMessage());
            System.exit(1);
        }

        int clientCounter = 0;

        while (true) {
            try (Socket clientSocket = serverSocket.accept()) {
                clientCounter++;

                InetSocketAddress remoteAddress =
                        (InetSocketAddress) clientSocket.getRemoteSocketAddress();
                String clientIP = remoteAddress.getAddress().getHostAddress();
                int clientPort = remoteAddress.getPort();

                System.out.println("[" + clientCounter + "] Połączono z klientem: "
                        + clientIP + ":" + clientPort);

                try (InputStream in = clientSocket.getInputStream();
                     OutputStream out = clientSocket.getOutputStream()) {

                    byte[] buffer = new byte[1024];
                    int bytesRead;

                    while ((bytesRead = in.read(buffer)) != -1) {
                        String receivedText = new String(buffer, 0, bytesRead);
                        System.out.println("[" + clientCounter + "] Otrzymano " + bytesRead
                                + " B: \"" + receivedText + "\"");

                        out.write(buffer, 0, bytesRead);
                        out.flush();
                    }
                } catch (IOException e) {
                    System.out.println("[" + clientCounter + "] Błąd komunikacji: " + e.getMessage());
                }

                System.out.println("[" + clientCounter + "] Rozłączono klienta: "
                        + clientIP + ":" + clientPort);

            } catch (IOException e) {
                System.err.println("Błąd przy obsłudze klienta: " + e.getMessage());
            }
        }
    }
}
