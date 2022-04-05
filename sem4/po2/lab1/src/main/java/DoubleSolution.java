import com.google.common.collect.Lists;

import java.math.BigDecimal;
import java.math.MathContext;
import java.util.List;

public class DoubleSolution implements QESolvable {
    @Override
    public List<BigDecimal> solve(DeltaSolver deltaSolution) {
        MathContext mc = new MathContext("10");
        return Lists.newArrayList(
                deltaSolution
                        .b
                        .multiply(new BigDecimal("-1"))
                        .add(deltaSolution.getDelta().sqrt(mc))
                        .divide(deltaSolution.a.multiply(new BigDecimal("2")))
                ,
                deltaSolution
                        .b
                        .multiply(new BigDecimal("-1"))
                        .subtract(deltaSolution.getDelta().sqrt(mc))
                        .divide(deltaSolution.a.multiply(new BigDecimal("2")))
        );

    }
}
