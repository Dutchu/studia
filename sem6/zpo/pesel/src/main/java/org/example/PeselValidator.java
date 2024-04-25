package org.example;

import java.time.LocalDate;
import java.time.LocalDateTime;

public class PeselValidator {

    public void parse(String pesel) {
        if (pesel == null || pesel.length() != 11) {
            throw new WrongValuesPeselException("Invalid PESEL number!");
        }

        int[] weights = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
        int sum = 0;

        for (int i = 0; i < weights.length; i++) {
            sum += weights[i] * Character.getNumericValue(pesel.charAt(i));
        }

        int checksum = (10 - (sum % 10)) % 10;
        if (checksum != Character.getNumericValue(pesel.charAt(10))) {
            throw new WrongValuesPeselException("Invalid PESEL number!");
        }

    }

    public char getGender(String pesel) {
        try {
            parse(pesel);
        } catch (WrongValuesPeselException e) {
            e.getMessage();
        }

        int genderDigit = Character.getNumericValue(pesel.charAt(9));
        return genderDigit % 2 == 0 ? 'K' : 'M';
    }

    public LocalDateTime getBirthDate(String pesel) {
        try {
            parse(pesel);
        } catch (WrongValuesPeselException e) {
            e.getMessage();
        }

        // Extract birth date from PESEL number
        int year = Integer.parseInt(pesel.substring(0, 2));
        int month = Integer.parseInt(pesel.substring(2, 4));
        int day = Integer.parseInt(pesel.substring(4, 6));
        LocalDateTime peselBirthDate = LocalDateTime.of(year, month, day, 0, 0);

        // Compare with input birth date and gender
        return peselBirthDate;
    }
}
