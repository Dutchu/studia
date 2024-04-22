package org.example;

import java.util.Scanner;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );

       PeselReader pr = new PeselReader();
        System.out.println(pr.read("pesele.txt"));
    }
}
