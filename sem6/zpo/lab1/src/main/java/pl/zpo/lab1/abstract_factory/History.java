package pl.zpo.lab1.abstract_factory;

import java.math.BigInteger;

public class History implements Publisherable {

    private final String author;
    private final String title;
    private final BigInteger numberOfPages;

    public History(String author, String title, BigInteger numberOfPages) {
        this.author = author;
        this.title = title;
        this.numberOfPages = numberOfPages;
    }

    @Override
    public String toString() {
        return "History{" +
                "author='" + author + '\'' +
                ", title='" + title + '\'' +
                ", numberOfPages=" + numberOfPages +
                '}';
    }
}
