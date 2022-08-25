package client;

import data.Notification;
import exceptions.WrongInputException;

import java.io.*;
import java.net.Socket;
import java.security.Timestamp;
import java.util.Date;
import java.util.Scanner;
import java.util.Timer;

public class Client {

    private Socket socket;
//    private BufferedReader bufferedReader;
//    private BufferedWriter bufferedWriter;
    private ObjectInputStream inputStream;
    private ObjectOutputStream outputStream;
    private String userName;


    public Client(Socket socket, String username) {
        try {
            this.socket = socket;
//            this.bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
//            this.bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            this.inputStream = new ObjectInputStream(socket.getInputStream());
            this.outputStream = new ObjectOutputStream(socket.getOutputStream());

            this.userName = username;
        } catch (IOException e) {
            closeAll(socket, inputStream, outputStream);
            e.printStackTrace();
        }
    }

    public void sendMessage() {
        try {
//            bufferedWriter.write(userName);
//            bufferedWriter.newLine();
//            bufferedWriter.flush();

            Scanner scanner = new Scanner(System.in);
            Date date = new Date();

            while (socket.isConnected()) {
                String messageToSend;

                try {

                    messageToSend = scanner.nextLine();
                    if (messageToSend.length() > 100) throw new WrongInputException("length: " + messageToSend.length() + " > 100!");
//                    bufferedWriter.write(messageToSend);
//                    bufferedWriter.newLine( );
//                    bufferedWriter.flush();

                    /*
                     New feature
                     */
                    Notification notification = new Notification(userName, messageToSend, new Date(date.getTime() + 100000));
                    outputStream.writeObject(notification);

                } catch (WrongInputException inputException) {
                    System.err.println("Input too long");
                    inputException.printStackTrace();
                }


            }
        } catch (IOException e) {
            System.out.println("INFO: Connection breakdown. Can't send messages!");
            closeAll(socket, inputStream, outputStream);
            e.printStackTrace();
        }
    }

    public void listenForMessage() {
        new Thread(new Runnable() {
            @Override
            public void run() {

                Notification incomingNotification;
                while (socket.isConnected()) {
                    try {
                        incomingNotification = (Notification) inputStream.readObject();

                        if (incomingNotification == null) throw new IOException();
                        System.out.println(incomingNotification);
                    } catch (IOException | ClassNotFoundException e) {
                        System.out.println("INFO: Connection breakdown. Can't fetch messages!");
                        closeAll(socket, inputStream, outputStream);
                        e.printStackTrace();
                        break;
                    }
                }
            }
        }).start();
        System.out.println("INFO: Stopping to listen.");
    }

    private void closeAll(Socket socket, ObjectInputStream inputStream, ObjectOutputStream outputStream) {
        System.out.println("INFO: Closing connections!");
        try {
            if ( socket != null )
                socket.close();
            if ( inputStream != null )
                inputStream.close();
            if ( outputStream != null )
                outputStream.close();
        } catch (IOException e) {
            System.err.println("INFO: Could not close connections!");
            e.printStackTrace();
        }
    }


    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username for group chat");
        String username = scanner.nextLine();

        Socket socket = new Socket("localhost", 6969);
        Client client = new Client(socket, username);
        client.sendMessage();
        client.listenForMessage();
        System.out.println("Bye Bye!");
    }
}
