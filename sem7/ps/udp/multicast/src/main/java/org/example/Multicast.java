package org.example;

/**
 * Hello world!
 *
 */
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.util.Scanner;

public class Client {
    private static final int BUFFER_SIZE = 1024;
    private InetAddress group;
    private int port;
    private MulticastSocket socket;

    public Client(String groupAddress, int port) throws IOException {
        this.group = InetAddress.getByName(groupAddress);
        this.port = port;
        socket = new MulticastSocket(port);
        socket.setReuseAddress(true);
        socket.joinGroup(group);
    }

    public void sendMessage(String message) {
        try {
            byte[] buffer = message.getBytes();
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length, group, port);
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
        try {
            socket.leaveGroup(group);
            socket.close();
        } catch(IOException ex) {
            System.err.println("Błąd przy zamykaniu socketu: " + ex.getMessage());
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Podaj adres IP grupy multicast: ");
            String groupAddress = scanner.nextLine();
            System.out.print("Podaj numer portu: ");
            int port = Integer.parseInt(scanner.nextLine());

            Client chat = new Client(groupAddress, port);
            chat.receiveMessages();
            System.out.println("Wpisz wiadomość do wysłania (wpisz 'exit' aby zakończyć): ");
            while (true) {
                String message = scanner.nextLine();
                if ("exit".equalsIgnoreCase(message)) {
                    break;
                }
                chat.sendMessage(message);
            }
            chat.close();
        } catch(Exception ex) {
            System.err.println("Błąd: " + ex.getMessage());
        } finally {
            scanner.close();
        }
    }
}
