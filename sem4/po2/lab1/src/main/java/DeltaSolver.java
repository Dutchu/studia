import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class DeltaSolver {

    BigDecimal delta;
    BigDecimal a;
    BigDecimal b;
    BigDecimal c;

    public DeltaSolver() {
        this.a = BigDecimal.ZERO;
        this.b = BigDecimal.ZERO;
        this.c = BigDecimal.ZERO;
        this.delta = BigDecimal.ZERO;
    }

    public DeltaSolver(BigDecimal a, BigDecimal b, BigDecimal c) {
        this.a = a;
        this.b = b;
        this.c = c;
        this.delta = b.pow(2).subtract(a.multiply(c).multiply(new BigDecimal(4)));

    }

    public BigDecimal getDelta() {
        return this.delta;
    }

}
