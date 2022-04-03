import java.math.BigDecimal;

public class QuadraticEquationFactory {

    private BigDecimal a;
    private BigDecimal b;
    private BigDecimal c;

    public QuadraticEquationSolver getSolution(BigDecimal a, BigDecimal b, BigDecimal c){
        DeltaSolver deltaSolver = new DeltaSolver(a, b, c);
        BigDecimal delta = deltaSolver.getDelta();

        if(delta.compareTo( new BigDecimal("0") ) ){

        }
    }

}
