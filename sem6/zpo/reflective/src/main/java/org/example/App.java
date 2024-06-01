package org.example;

import org.example.calculator.OperationFactory;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
        System.out.println(OperationFactory.getOperation("+").calculate(1, 2));

    }
}
