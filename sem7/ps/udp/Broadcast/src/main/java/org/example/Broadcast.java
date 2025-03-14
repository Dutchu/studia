package org.example;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;

public class Broadcast {
    private static final int BUFFER_SIZE = 1024;
    private int port;
    private DatagramSocket socket;

    public Broadcast(int port) throws SocketException {
        this.port = port;
        socket = new DatagramSocket(port);
        socket.setReuseAddress(true);
    }

    public void sendMessage(String message, String broadcastAddress) {
        try {
            byte[] buffer = message.getBytes();
            InetAddress address = InetAddress.getByName(broadcastAddress);
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, address, port);
            socket.send(packet);
        } catch(IOException ex) {
            System.err.println("Błąd przy wysyłaniu wiadomości: " + ex.getMessage());
        }
    }

    public void receiveMessages() {
        new Thread(() -> {
            byte[] buffer = new byte[BUFFER_SIZE];
            while (true) {
                try {
                    DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                    socket.receive(packet);
                    String received = new String(packet.getData(), 0, packet.getLength());
                    System.out.println("Odebrano: " + received);
                } catch(IOException ex) {
                    System.err.println("Błąd przy odbieraniu wiadomości: " + ex.getMessage());
                    break;
                }
            }
        }).start();
    }

    public void close() {
        socket.close();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Podaj numer portu: ");
            int port = Integer.parseInt(scanner.nextLine());
            System.out.print("Podaj adres rozgłoszeniowy (broadcast, np. 255.255.255.255): ");
            String broadcastAddress = scanner.nextLine();

            Broadcast chat = new Broadcast(port);
            chat.receiveMessages();
            System.out.println("Wpisz wiadomość do wysłania (wpisz 'exit' aby zakończyć): ");
            while (true) {
                String message = scanner.nextLine();
                if ("exit".equalsIgnoreCase(message)) {
                    break;
                }
                chat.sendMessage(message, broadcastAddress);
            }
            chat.close();
        } catch(Exception ex) {
            System.err.println("Błąd: " + ex.getMessage());
        } finally {
            scanner.close();
        }
    }
}
