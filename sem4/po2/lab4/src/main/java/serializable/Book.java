package serializable;

import java.io.Serial;
import java.io.Serializable;

public class Book implements Serializable {
    @Serial
    private static final long serialVersionUID = -2936687026040726549L;
    private String bookName;
    private transient String description;
    private transient int copies;

    public String getBookName() {
        return bookName;
    }
    public String getDescription() {
        return description;
    }
    public int getCopies() {
        return copies;
    }

    public void setBookName(String bookName) {
        this.bookName = bookName;
    }
    public void setDescription(String description) {
        this.description = description;
    }
    public void setCopies(int copies) {
        this.copies = copies;
    }
}
