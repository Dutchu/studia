import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class DeltaSolver {

    BigDecimal delta;

    public DeltaSolver(BigDecimal a, BigDecimal b, BigDecimal c) {

        this.delta = b.pow(2).subtract(a.multiply(c).multiply(new BigDecimal(4)));

    }

    public BigDecimal getDelta() {
        return this.delta;
    }

}
