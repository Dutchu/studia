import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Timer;

public class Server {
    public static final int PORT = 6969;

    public static void main(String[] args) {
        try {
            new Server();
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public Server() throws IOException, ClassNotFoundException {
        ServerSocket serverSocket = new ServerSocket(PORT);
        Socket socket = serverSocket.accept();

        ObjectOutputStream outputStream = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream());

        Notification receivedNotification = (Notification) inputStream.readObject();

        System.out.println(receivedNotification);


        SendNotification task = new SendNotification(receivedNotification, outputStream);
        Timer timer = new Timer("Notifications");
        timer.schedule(
                task,
                receivedNotification.getTime()
        );

        serverSocket.close();
    }
}
