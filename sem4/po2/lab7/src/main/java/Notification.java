import java.io.Serializable;
import java.util.Date;

public class Notification implements Serializable, Comparable<Notification> {
    private String author;
    private String content;
    private Date time;

    public Notification(String author, String content, Date time) {
        this.author = author;
        this.content = content;
        this.time = time;
    }

    @Override
    public String toString() {
        return "Notification{" +
                "author='" + author + '\'' +
                ", content='" + content + '\'' +
                ", time=" + time +
                '}';
    }

    @Override
    public int compareTo(Notification otherDate) {
        return time.compareTo(otherDate.getTime());
    }

    public String getAuthor() {
        return author;
    }

    public String getContent() {
        return content;
    }

    public Date getTime() {
        return time;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public void setTime(Date time) {
        this.time = time;
    }
}
