package pl.zpo.lab1.decorator;

public abstract class DecoratableBookDecorator implements DecoratableBook {

    protected DecoratableBook decoratableBookToDecorate;
    public DecoratableBookDecorator(DecoratableBook decoratableBook) {
        this.decoratableBookToDecorate = decoratableBook;
    }

//    @Override
//    public String decorate(DecoratableBook decoratableBook) {
//        return decoratableBookToDecorate.decorate(decoratableBook);
//    }

    @Override
    public String toString() {
        return decoratableBookToDecorate.toString();
    }

}
