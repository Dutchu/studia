package pl.zpo.lab1.abstract_factory;

import java.math.BigInteger;

public class Thriller implements Publisherable {
    private final String author;
    private final String title;
    private final BigInteger numberOfPages;

    public Thriller(String author, String title, BigInteger numberOfPages) {
        this.author = author;
        this.title = title;
        this.numberOfPages = numberOfPages;
    }

    @Override
    public String toString() {
        return "Thriller{" +
                "author='" + author + '\'' +
                ", title='" + title + '\'' +
                ", numberOfPages=" + numberOfPages +
                '}';
    }
}
