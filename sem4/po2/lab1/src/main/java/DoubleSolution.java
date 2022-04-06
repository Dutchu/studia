import com.google.common.collect.Lists;

import java.math.BigDecimal;
import java.math.MathContext;
import java.util.List;

public class DoubleSolution implements QESolvable {

    private final DeltaSolver deltaSolver;

    DoubleSolution(DeltaSolver deltaSolver) {
        this.deltaSolver = new DeltaSolver();
        this.deltaSolver.delta = deltaSolver != null ? deltaSolver.getDelta() : BigDecimal.ZERO;
        this.deltaSolver.a = deltaSolver != null ? deltaSolver.a : BigDecimal.ZERO;
        this.deltaSolver.b = deltaSolver != null ? deltaSolver.b : BigDecimal.ZERO;
        this.deltaSolver.c = deltaSolver != null ? deltaSolver.c : BigDecimal.ZERO;
    }

    @Override
    public List<BigDecimal> solve() {
        MathContext mc = new MathContext("10");
        return Lists.newArrayList(
                deltaSolver
                        .b
                        .multiply(new BigDecimal("-1"))
                        .add(deltaSolver.getDelta().sqrt(mc))
                        .divide(deltaSolver.a.multiply(new BigDecimal("2")), mc)
                ,
                deltaSolver
                        .b
                        .multiply(new BigDecimal("-1"))
                        .subtract(deltaSolver.getDelta().sqrt(mc))
                        .divide(deltaSolver.a.multiply(new BigDecimal("2")), mc)
        );

    }
}
