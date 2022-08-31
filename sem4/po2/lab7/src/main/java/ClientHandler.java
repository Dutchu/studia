import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Timer;

public class ClientHandler implements Runnable{

    public static ArrayList<ClientHandler> clientHandlers = new ArrayList<>();
    private Socket clientSocket;
    private ObjectInputStream in;
    private ObjectOutputStream out;
    private String clientUsername;
    private final List<Notification> notifications = new ArrayList<>();


    private void closeAll(Socket socket, ObjectOutputStream out, ObjectInputStream in) {
        removeClient();
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

    private void removeClient() {
        System.out.println("Client " + this.clientUsername + " has been removed!");
        clientHandlers.remove(this);
    }

    public ClientHandler(Socket socket) {

        try {
            this.clientSocket = socket;
            in = new ObjectInputStream(clientSocket.getInputStream());
            out = new ObjectOutputStream(clientSocket.getOutputStream());
            clientHandlers.add(this);
            Notification clientName = (Notification) in.readObject();
            clientUsername = clientName.getContent();

        } catch (IOException | ClassNotFoundException e) {
            closeAll(socket, out, in);
            e.printStackTrace();
        }

    }


    @Override
    public void run() {

        Notification notificationFromClient = null;

        while (clientSocket.isConnected()) {
            try {

                //Keep reading objects
                notificationFromClient = (Notification) in.readObject();
                notificationFromClient.setTime(new Date(new Date().getTime() + 10000));
                notifications.add(notificationFromClient);
                notifications.sort(Notification::compareTo);
                System.out.println("New message received!"
                        + " From: " + notificationFromClient.getAuthor()
                        + " Message: " + notificationFromClient.getContent()
                        + " At: " + notificationFromClient.getTime());

                //Schedule new tasks to send notifications for every notification that came
                Notification notificationToSend = notifications.stream().findFirst().orElse(new Notification("ERROR", "ERROR", new Date(new Date().getTime() + 100)));
                System.out.println(notifications);
                SendNotification task = new SendNotification(notificationToSend, out);
                Timer timer = new Timer("Notifications");
                timer.schedule(
                        task,
                        notificationToSend.getTime()
                );

                notifications.remove(notificationToSend);
                System.out.println(notifications);

            } catch (IOException | ClassNotFoundException e) {
                closeAll(clientSocket, out, in);
                break;
            }
        }

    }
}
