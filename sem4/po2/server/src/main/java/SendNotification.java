import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.Date;
import java.util.TimerTask;

public class SendNotification extends TimerTask {

    private final Date date = new Date();
    private Notification notificationToSend;
    private ObjectOutputStream out;


    @Override
    public void run() {
        try {
            notificationToSend.setAuthor("SERVER");
            notificationToSend.setContent(notificationToSend.getContent() + "... with love, Yours ~Server");
            notificationToSend.setTime(date);
            out.writeObject(notificationToSend);
        } catch (IOException e) {
            System.err.println("Failed to send notification");
            e.printStackTrace();
            closeConnection();
        }
    }

    private void closeConnection() {
        try {

            out.close();
        } catch (IOException e) {
            System.err.println("Unable to close connection");
            e.printStackTrace();
        }
    }

    public SendNotification(Notification notificationToSend, ObjectOutputStream out) {
        this.notificationToSend = notificationToSend;
        this.out = out;
    }

    public Notification getNotificationToSend() {
        return notificationToSend;
    }

    public void setNotificationToSend(Notification notificationToSend) {
        this.notificationToSend = notificationToSend;
    }

    public ObjectOutputStream getOut() {
        return out;
    }

    public void setOut(ObjectOutputStream out) {
        this.out = out;
    }


}
