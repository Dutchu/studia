package pl.zpo.lab1.abstract_factory;

import java.math.BigInteger;

public class ThrillerFactory implements PublisherFactory {

    @Override
    public Publisherable createBook(String title, BigInteger numberOfPages) {
        return new Poem("Remigiusz Mróz", title, numberOfPages);
    }
}
