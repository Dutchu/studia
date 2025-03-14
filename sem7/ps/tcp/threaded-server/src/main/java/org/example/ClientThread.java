package org.example;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

class ClientThread extends Thread {

    private final Socket clientSocket;
    private final int clientNumber;

    public ClientThread(Socket clientSocket, int clientNumber) {
        this.clientSocket = clientSocket;
        this.clientNumber = clientNumber;
    }

    @Override
    public void run() {
        String clientIP = clientSocket.getInetAddress().getHostAddress();
        int clientPort = clientSocket.getPort();

        try (Socket s = clientSocket;
             InputStream in = s.getInputStream();
             OutputStream out = s.getOutputStream()) {

            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = in.read(buffer)) != -1) {
                String receivedText = new String(buffer, 0, bytesRead);
                System.out.println("[" + clientNumber + "] Otrzymano (" + bytesRead + " B): \""
                        + receivedText + "\"");

                out.write(buffer, 0, bytesRead);
                out.flush();
            }
        } catch (IOException e) {
            System.out.println("[" + clientNumber + "] Błąd komunikacji: " + e.getMessage());
        } finally {
            ThreadedEchoServer.decrementActiveConnections();

            System.out.println("[" + clientNumber + "] Rozłączono klienta: "
                    + clientIP + ":" + clientPort);
        }
    }
}
