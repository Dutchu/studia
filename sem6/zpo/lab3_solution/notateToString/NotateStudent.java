package org.example.notateToString;

import java.lang.reflect.Field;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class NotateStudent {
    @NotateToString(comment = "numer indeksu", order = 2)
    private int indeks;

    @NotateToString(comment = "Lista ocen", order = 3)
    private List<Float> oceny;

    @NotateToString(comment = "Nazwisko", order = 1)
    private String nazwisko;

    private String imie;

    private boolean dzienny;

    public NotateStudent(int indeks, List<Float> oceny, String nazwisko, String imie, boolean dzienny) {
        this.indeks = indeks;
        this.oceny = oceny;
        this.nazwisko = nazwisko;
        this.imie = imie;
        this.dzienny = dzienny;
    }

    @Override
    public String toString() {
        Class<?> clazz = this.getClass();
        List<FieldDisplay> fieldDisplays = new ArrayList<>();

        for (Field field : clazz.getDeclaredFields()) {
            if (field.isAnnotationPresent(NotateToString.class)) {
                NotateToString displayAnno = field.getAnnotation(NotateToString.class);
                field.setAccessible(true);
                try {
                    Object value = field.get(this);
                    String formatted = displayAnno.comment() + ": " + value;
                    fieldDisplays.add(new FieldDisplay(displayAnno.order(), formatted));
                } catch (IllegalAccessException e) {
                    System.err.println(e.getMessage());
                }
            }
        }

        fieldDisplays.sort(Comparator.comparingInt(FieldDisplay::getOrder));

        return fieldDisplays.stream()
                .map(FieldDisplay::getDisplay)
                .collect(Collectors.joining(", "));
    }

    private static class FieldDisplay {
        private final int order;
        private final String display;

        public FieldDisplay(int order, String display) {
            this.order = order;
            this.display = display;
        }

        public int getOrder() {
            return order;
        }

        public String getDisplay() {
            return display;
        }
    }
}
