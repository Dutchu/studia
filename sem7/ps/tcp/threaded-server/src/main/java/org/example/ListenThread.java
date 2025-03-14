package org.example;

import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

class ListenThread extends Thread {

    private final ServerSocket serverSocket;

    public ListenThread(ServerSocket serverSocket) {
        this.serverSocket = serverSocket;
    }

    @Override
    public void run() {
        while (!isInterrupted()) {
            try {
                Socket clientSocket = serverSocket.accept();

                int clientNumber = ThreadedEchoServer.getAndIncrementClientCounter();

                InetSocketAddress remoteAddr =
                        (InetSocketAddress) clientSocket.getRemoteSocketAddress();
                String clientIP = remoteAddr.getAddress().getHostAddress();
                int clientPort = remoteAddr.getPort();

                System.out.println("[" + clientNumber + "] Połączenie od: "
                        + clientIP + ":" + clientPort);

                int currentActive = ThreadedEchoServer.getActiveConnections();
                if (currentActive >= ThreadedEchoServer.getMaxConnections()) {
                    System.out.println("[" + clientNumber + "] Odrzucono połączenie (SERVER BUSY).");

                    try (OutputStream out = clientSocket.getOutputStream()) {
                        out.write("SERVER BUSY\n".getBytes());
                        out.flush();
                    } catch (IOException e) {
                    }
                    clientSocket.close();
                } else {
                    ThreadedEchoServer.incrementActiveConnections();

                    new ClientThread(clientSocket, clientNumber).start();
                }

            } catch (IOException e) {
                if (!serverSocket.isClosed()) {
                    System.err.println("Błąd w wątku nasłuchującym: " + e.getMessage());
                }
                break;
            }
        }
        System.out.println("Wątek nasłuchujący zakończył pracę.");
    }
}
