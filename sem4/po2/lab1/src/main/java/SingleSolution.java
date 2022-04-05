import com.google.common.collect.Lists;
import org.w3c.dom.ls.LSOutput;

import java.math.BigDecimal;
import java.math.MathContext;
import java.util.List;

public class SingleSolution implements QESolvable {

    private DeltaSolver deltaSolver;

    SingleSolution(DeltaSolver deltaSolver) {
        this.deltaSolver = new DeltaSolver();
        this.deltaSolver.delta = deltaSolver != null ? deltaSolver.getDelta() : (
                System.out.println("xds"),
                BigDecimal.ZERO;
                );
        this.deltaSolver.a = deltaSolver != null ? deltaSolver.a : BigDecimal.ZERO;
        this.deltaSolver.b = deltaSolver != null ? deltaSolver.b : BigDecimal.ZERO;
        this.deltaSolver.c = deltaSolver != null ? deltaSolver.c : BigDecimal.ZERO;
    }

    @Override
    public List<BigDecimal> solve(DeltaSolver deltaSolution) {
        MathContext mc = new MathContext("10");
        return Lists.newArrayList(
                deltaSolution
                        .b.negate()
                        .divide(BigDecimal.valueOf(2.0).multiply(deltaSolution.a), mc));
    }
}
