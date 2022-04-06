import java.math.BigDecimal;

public class QESolverFactory {

    public QESolvable calcDelta(DeltaSolver deltaSolver) {

        int ifDeltaComparedZero = deltaSolver.getDelta().compareTo(BigDecimal.ZERO);

        if(ifDeltaComparedZero == 0) {
            return new SingleSolution(deltaSolver);
        }
        if(ifDeltaComparedZero > 0) {
            return new DoubleSolution(deltaSolver);
        }
        if(ifDeltaComparedZero < 0) {
            return new NoSolution();
        }
        return null;
    }
}
