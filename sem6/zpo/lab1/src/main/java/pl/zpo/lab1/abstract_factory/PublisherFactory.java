package pl.zpo.lab1.abstract_factory;


import java.math.BigInteger;

public interface PublisherFactory {

    public abstract Publisherable createBook(String title, BigInteger numberOfPages);

}
