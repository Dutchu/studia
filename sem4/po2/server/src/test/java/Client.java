import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Date;

public class Client {
    public Client() throws IOException {
        Socket socket = new Socket("localhost", Server.PORT);

        ObjectOutputStream outputStream = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream inputStream = new ObjectInputStream(socket.getInputStream());
        Date date = new Date();

        Notification toSend = new Notification("Client", "Elo szmaty!", new Date(date.getTime() + 6000));
        outputStream.writeObject(toSend);

        Notification receivedNotification = null;
        try {
            receivedNotification = (Notification) inputStream.readObject();
        } catch (ClassNotFoundException e) {
            System.err.println("SERVER: Couldn't read object!");
            e.printStackTrace();
        }

        System.out.println(receivedNotification);

        outputStream.close();
        socket.close();
    }

    public static void main(String[] args) {
        try {
            new Client();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
