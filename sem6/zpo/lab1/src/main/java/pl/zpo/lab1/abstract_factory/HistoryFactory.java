package pl.zpo.lab1.abstract_factory;


import java.math.BigInteger;

public class HistoryFactory implements PublisherFactory {

    @Override
    public Publisherable createBook(String title, BigInteger numberOfPages) {
        return new Poem("Henryk Sienkiewicz", title, numberOfPages);
    }
}
