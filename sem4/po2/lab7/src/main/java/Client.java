import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Date;
import java.util.Scanner;

public class Client {

    private Socket socket;
    private String userName;
    private ObjectOutputStream outputStream;
    private ObjectInputStream inputStream;

    public Client(Socket socket, String username) throws IOException {
        this.socket = socket;
        this.userName = username;
        outputStream = new ObjectOutputStream(socket.getOutputStream());
        inputStream = new ObjectInputStream(socket.getInputStream());

//        Socket socket = null;
//        try {
//            socket = new Socket("localhost", Server.PORT);
//        } catch (ConnectException e) {
//            e.printStackTrace();
//        }
//
//        if (socket != null && socket.isConnected()) {
//            System.out.println("socked already in use");
//        } else {
//            System.out.println("socked is free");
//        }
//
//        ObjectOutputStream outputStream = new ObjectOutputStream(socket.getOutputStream());
//        ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream());
//        Date date = new Date();
//
//        Notification toSend = new Notification("Client", "Elo szmaty!", new Date(date.getTime() + 6000));
//        outputStream.writeObject(toSend);
//
//        Notification receivedNotification = null;
//        try {
//            receivedNotification = (Notification) inputStream.readObject();
//        } catch (ClassNotFoundException e) {
//            System.err.println("SERVER: Couldn't read object!");
//            e.printStackTrace();
//        }
//
//        System.out.println(receivedNotification);
//
//        outputStream.close();
//        socket.close();
    }

    private void sendMessage() {
        try {
            Scanner scanner = new Scanner(System.in);
            String messageToSend;
            Integer interval;
            Notification notification;
            outputStream.writeObject(new Notification(userName, userName, new Date()));

            while (socket.isConnected()) {

                System.out.print("Enter message: ");
                messageToSend = scanner.nextLine();

                if (messageToSend.length() > 100) throw new WrongInputException("length: " + messageToSend.length() + " > 100!");

                System.out.print("Enter interval: ");
                interval = scanner.nextInt();
                scanner.nextLine();


                notification = new Notification(userName, messageToSend, new Date(new Date().getTime() + interval));
                outputStream.writeObject(notification);

            }
        } catch (IOException | WrongInputException e) {
            closeAll(socket, outputStream, inputStream);
            e.printStackTrace();
        }
    }


    public void listenForMessage() {
        new Thread(() -> {
            System.out.println("Listening on port: " + socket.getPort());
            Notification incomingNotification;
            while (socket.isConnected()) {
                try {

                    incomingNotification = (Notification) inputStream.readObject();
                    if (incomingNotification == null) throw new IOException();
                    System.out.println(incomingNotification);
                } catch (IOException | ClassNotFoundException e) {
                    System.out.println("INFO: Connection breakdown. Can't fetch messages!");
                    closeAll(socket, outputStream, inputStream);
                    e.printStackTrace();
                    break;
                }
            }
            System.out.println("INFO: Stopping to listen.");
        }).start();

    }

    private void closeAll(Socket socket, ObjectOutputStream out, ObjectInputStream in) {
        try {
            if (socket != null) {
                socket.close();
            }
            if (out != null) {
                out.close();
            }
            if (in != null) {
                in.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username for group chat");
        String username = scanner.nextLine();

        Socket socket = null;
        Client client = null;
        try {
            socket = new Socket("localhost", 6969);
            client = new Client(socket, username);
        } catch (IOException e) {
            e.printStackTrace();
        }
        client.listenForMessage();
        client.sendMessage();
        System.out.println("Client stopped... ");
    }


}
