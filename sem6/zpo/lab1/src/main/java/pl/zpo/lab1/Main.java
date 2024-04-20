package pl.zpo.lab1;

import pl.zpo.lab1.abstract_factory.FactoryType;
import pl.zpo.lab1.abstract_factory.Publisher;
import pl.zpo.lab1.abstract_factory.Publisherable;
import pl.zpo.lab1.decorator.DecoratableBook;
import pl.zpo.lab1.decorator.DecorativeCoverDecoratableBook;
import pl.zpo.lab1.decorator.HardCoverDecoratableBook;
import pl.zpo.lab1.decorator.SimpleDecoratableBook;
import pl.zpo.lab1.singleton.Table;
import pl.zpo.lab1.singleton.TableException;

import java.math.BigInteger;

public class Main {
    public static void main(String[] args) {

        // Decorator
        DecoratableBook book = new SimpleDecoratableBook("Pan Tadeusz", "Adam Mickiewicz", BigInteger.valueOf(1834));
        book = new HardCoverDecoratableBook(book);
        book = new DecorativeCoverDecoratableBook(book);
        book = new HardCoverDecoratableBook(book);
        System.out.println(book);

        // Abstract Factory
        Publisherable toBePublished = Publisher.Factory.createPublisher(FactoryType.POEM).createBook("Irksome Pleasures", BigInteger.valueOf(1000));
        System.out.println(toBePublished);

        //Singleton
        Table table = Table.getInstance(1);
        try {
            table.addBook(book);
            table.addBook(book);
        } catch (TableException e) {
            System.err.println(e.getMessage());
        }
        System.out.println(table);

        Table.getInstance(2);

        NumberConverter numberConverter = new NumberConverter();
    }
}
