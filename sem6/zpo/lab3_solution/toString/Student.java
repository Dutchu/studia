package org.example.toString;

import org.example.equals.IgnoreEquals;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Student extends ToString {
    @IgnoreEquals
    private int indeks;

    @IgnoreEquals
    private List<Float> oceny = new ArrayList<>();

    private String imie;
    private String nazwisko;

    @IgnoreEquals
    private String stopien_studiow;

    public Student(int indeks, String imie, String nazwisko, String stopien_studiow, List<Float> oceny) {
        this.indeks = indeks;
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.stopien_studiow = stopien_studiow;
        this.oceny.addAll(oceny);
    }

    public int getIndeks() {
        return indeks;
    }

    public String getFirstName() {
        return imie;
    }

    public String getLastName() {
        return nazwisko;
    }

    public String getStopien_studiow() {
        return stopien_studiow;
    }

    public List<Float> getOceny() {
        return oceny;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Student other = (Student) obj;

        Field[] fields = this.getClass().getDeclaredFields();
        for (Field field : fields) {
            if (!field.isAnnotationPresent(IgnoreEquals.class)) {
                try {
                    field.setAccessible(true);
                    Object thisValue = field.get(this);
                    Object otherValue = field.get(other);
                    if (!Objects.equals(thisValue, otherValue)) {
                        return false;
                    }
                } catch (IllegalAccessException e) {
                    throw new RuntimeException(e);
                }
            }
        }
        return true;
    }

    @Override
    public int hashCode() {
        Field[] fields = this.getClass().getDeclaredFields();
        return Arrays.stream(fields)
                .filter(field -> !field.isAnnotationPresent(IgnoreEquals.class))
                .peek(field -> field.setAccessible(true))
                .map(field -> {
                    try {
                        return field.get(this);
                    } catch (IllegalAccessException e) {
                        throw new RuntimeException(e);
                    }
                })
                .filter(Objects::nonNull)
                .mapToInt(Object::hashCode)
                .sum();
    }

}
