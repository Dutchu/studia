package pl.zpo.lab1.singleton;

import pl.zpo.lab1.decorator.DecoratableBook;
import java.util.Stack;

public final class Table {
    private final Stack<DecoratableBook> decoratableBooks;
    private final int maxBooks;
    private static volatile Table instance;

    private Table(int maxBooks) throws TableException {

        if (instance != null) {
            throw new IllegalStateException("Already initialized");
        }

        if (maxBooks < 1) {
            throw new TableException("Table must have at least one book slot");
        }
        this.decoratableBooks = new Stack<>();
        this.maxBooks = maxBooks;
    }

    public static synchronized Table getInstance(int maxBooks) {
        if (instance == null) {
            try {
                instance = new Table(maxBooks);
            } catch (TableException e) {
                System.err.println(e.getMessage());
            }
        }
        return instance;
    }

    public void addBook(DecoratableBook book) throws TableException {
        if (this.decoratableBooks.size() == this.maxBooks) {
            throw new TableException("Table is full");
        }
        this.decoratableBooks.push(book);
    }

    public DecoratableBook removeBook() throws TableException {
        if (this.decoratableBooks.size() == 0) {
            throw new TableException("Table is empty");
        }
        return this.decoratableBooks.pop();
    }

    @Override
    public String toString() {
        return "Table{" +
                "decoratableBooks=" + decoratableBooks +
                ", maxBooks=" + maxBooks +
                '}';
    }
}
