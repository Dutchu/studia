package org.example;

/**
 * Hello world!
 *
 */
public class App 
{

    //write a static method to read file with
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
    }

    //mierzenie ilości zużywanej pamięci przez program
    //testy sprawdzające zużycie pamięci w czytaniu pliku
    //-Xmx20M
    //Ilość słów n dzielone przez 2. 29M /100 =>  29_500, wartość k=100 buffor na 100 słów. Dlaczego buffor na 100 słó to czmeu jest ich 6. Trzeba dać wartość większą od ilości (częstotliwość występowania) słó któe chcemy znaleźć
    // jeżeli po zmniejszeniu będzie 0, to wylatuje i zwalnia miejsce w słowniku. 100 słów, ale nie koniecznie wsytępujących tyle co N/100 najczęstrrzych słów.
}
