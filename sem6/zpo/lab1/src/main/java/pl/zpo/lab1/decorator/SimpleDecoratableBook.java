package pl.zpo.lab1.decorator;

import java.math.BigInteger;
import lombok.*;

@Getter @Setter
public class SimpleDecoratableBook implements DecoratableBook {

    private String title;
    private String author;
    private BigInteger noOfPages;
    public SimpleDecoratableBook(String title, String author, BigInteger noOfPages) {
        this.title = title;
        this.author = author;
        this.noOfPages = noOfPages;
    }

//    @Override
//    public String decorate(DecoratableBook decoratableBook) {
//        return "Book:{" + title + " by " + author + " with " + noOfPages + " pages}";
//    }

    @Override
    public String toString() {
        return "Book:{" + title + " by " + author + " with " + noOfPages + " pages}";
    }

}

