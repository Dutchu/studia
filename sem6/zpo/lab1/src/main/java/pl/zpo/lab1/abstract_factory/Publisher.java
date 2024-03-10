package pl.zpo.lab1.abstract_factory;

import lombok.Getter;
import lombok.Setter;

@Setter @Getter
public class Publisher {

    private Publisherable book;

    public static class Factory {
        public static PublisherFactory createPublisher(FactoryType type) {


            return switch (type) {
                case HISTORY -> new HistoryFactory();
                case POEM -> new PoemFactory();
                case THRILLER -> new ThrillerFactory();
                default -> throw new IllegalArgumentException("Unknown type: " + type);
            };

        }
    }
}
