package pl.zpo.lab1.decorator;


public class DecorativeCoverDecoratableBook extends DecoratableBookDecorator {

    public DecorativeCoverDecoratableBook(DecoratableBook decoratableBook) {
        super(decoratableBook);
    }

//    @Override
//    public String decorate(DecoratableBook decoratableBook) {
//        return super.decorate(decoratableBook);
//    }
    @Override
    public String toString() {
        return super.toString() + " with decorative cover";
    }
}

