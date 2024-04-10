package pl.zpo.lab1.decorator;

public class HardCoverDecoratableBook extends DecoratableBookDecorator {

    public HardCoverDecoratableBook(DecoratableBook decoratableBook) {
        super(decoratableBook);
    }

//    @Override
//    public String decorate(DecoratableBook decoratableBook) {
//        return super.decorate(decoratableBook);
//    }

    @Override
    public String toString() {
        return super.toString() + " with hard cover";
    }

}
