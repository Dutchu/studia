package server;

import data.Notification;
import exceptions.WrongInputException;

import java.io.*;
import java.net.Socket;
import java.util.*;

public class ClientHandler implements Runnable {

    public static ArrayList<ClientHandler> clientHandlers = new ArrayList<>();
    private Socket clientSocket;
//    private BufferedWriter out;
//    private BufferedReader in;
    private ObjectInputStream in;
    private ObjectOutputStream out;
    private String clientUsername;
    private final List<Notification> notifications = new ArrayList<>();
    private final Date date = new Date();


    public ClientHandler(Socket socket) {

        try {
            this.clientSocket = socket;
//            out = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
//            in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
//            this.clientUsername = in.readLine();
            in = new ObjectInputStream(clientSocket.getInputStream());
            out = new ObjectOutputStream(clientSocket.getOutputStream());

            clientHandlers.add(this);
            broadcastMessage(new Notification("SERVER", clientUsername + " has entered the chat!", date));
        } catch (IOException e) {
            closeAll(socket, out, in);
            e.printStackTrace();
        }

    }

    private void closeAll(Socket socket, ObjectOutputStream out, ObjectInputStream in) {
        removeClientHandler();
        try {
            if ( socket != null )
                socket.close();
            if ( out != null )
                out.close();
            if ( in != null )
                in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void broadcastMessage(Notification notificationToSend) {
        for (ClientHandler clientHandler : clientHandlers) {
            try {
//                if (!clientHandler.clientUsername.equals(clientUsername)) {
//                    clientHandler.out.write(clientHandler + ": " + messageToSend);
//                    clientHandler.out.newLine();
//                    clientHandler.out.flush();
//                }
                if (clientHandler.clientUsername.equals(clientUsername)) {
                    notificationToSend.setTime(new Date());
                    clientHandler.out.writeObject(notificationToSend);
                    clientHandler.out.flush();
                }
            } catch (IOException e) {
                closeAll(clientSocket, out, in);
                e.printStackTrace();
            }
        }
    }

    public void removeClientHandler() {
        clientHandlers.remove(this);
//        broadcastMessage("SERVER: " + clientUsername + " has left the chat!");
        broadcastMessage(new Notification("SERVER", clientUsername + " has left the chat!", new Date()));
    }


    @Override
    public void run() {
        Notification notificationFromClient = null;
//        String messageFromClient = null;
        while (clientSocket.isConnected()) {
            try {
//                messageFromClient = in.readLine();
                /*
                New feature
                 */
                notificationFromClient = (Notification) in.readObject();
                notifications.add(notificationFromClient);
                notifications.sort(Notification::compareTo);

                Notification notificationToSend = notifications.stream().findFirst().orElse(new Notification("ERROR", "ERROR", new Date(date.getTime() + 100)));

                TimerTask task = new TimerTask() {
                    public void run() {
                        try {
                            out.writeObject(notificationToSend);
                            out.flush();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                };

                Timer timer = new Timer("NotificationTimer", true);
                timer.schedule(
                        task,
                        notificationToSend.getTime()
                );

//                broadcastMessage(notificationFromClient);

            } catch (IOException | ClassNotFoundException e) {
                closeAll(clientSocket, out, in);
                e.printStackTrace();
                break;
            }

//            if ("BYE".equalsIgnoreCase(notificationFromClient)) {
//                closeAll(clientSocket, out, in);
//                break;
//            }

            System.out.println(notificationFromClient.toString());
        }

        try {
            in.close();
            out.close();
            clientSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    private Object pushNotification() {
        return new Object();
    }

}
