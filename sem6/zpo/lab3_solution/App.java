package org.example;


import org.example.notateToString.NotateStudent;
import org.example.toString.Student;

import java.util.Arrays;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) {
        // Zadanie 1 - toString
        Student student1 = new Student(123, "Bartłomiej", "Błaszczyk", "Inżynier",  Arrays.asList(3.5f, 4.0f));
        Student student2 = new Student(456, "Jan", "Nowak", "Magister", Arrays.asList(3.0f, 4.5f));
        Student student3 = new Student(456, "Bartłomiej", "Błaszczyk", "Magister", Arrays.asList(3.0f, 4.5f));

        // Zadanie 2 - equals
        System.out.println(student1 + "\n" + student2 + "\n" + student3);
        System.out.println(student1.equals(student2));
        System.out.println(student1.equals(student3));

        // Zadanie 3 - notateToString
        NotateStudent student4 = new NotateStudent(236382,  Arrays.asList(3.5f, 4.0f, 3.0f, 5.0f), "Blaszczyk", "Bartlomiej", false);
        System.out.println(student4);
    }
}
