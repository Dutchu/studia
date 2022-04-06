import java.math.BigDecimal;
import java.util.List;

/***
 *                 deltaSolution -> deltaSolution
 *                         .b
 *                         .multiply(new BigDecimal("-1"))
 *                         .add(deltaSolution.getDelta().sqrt(mc))
 *                         .divide(deltaSolution.a.multiply(new BigDecimal("2")))
 */

public interface QESolvable {
    public List<BigDecimal> solve();
}
