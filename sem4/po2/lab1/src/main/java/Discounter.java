import java.math.BigDecimal;
import java.util.function.UnaryOperator;


/***
 * Example of "Strategy" functional Design Pattern
 */
public interface Discounter extends UnaryOperator<BigDecimal> {
    default Discounter combine(Discounter after) {
        return value -> after.apply(this.apply(value));
    }
}