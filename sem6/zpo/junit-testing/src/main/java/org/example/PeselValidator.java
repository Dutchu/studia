package org.example;

import java.time.DateTimeException;
import java.time.LocalDate;
import java.time.LocalDateTime;

public class PeselValidator {

    public void parse(String pesel) throws WrongValuesPeselException {
        if (pesel == null || pesel.length() != 11) {
            throw new WrongValuesPeselException("Wrong PESEL length!");
        }

        int[] weights = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
        int sum = 0;
        try {
            for (int i = 0; i < weights.length; i++) {
                sum += weights[i] * Character.getNumericValue(pesel.charAt(i));
            }
        } catch (NumberFormatException e) {
            throw new WrongValuesPeselException("Characters in PESEL number!");
        }

//        //exception - day > 31 | month > 12 |
//        if (Character.getNumericValue(pesel.charAt(4)) > 3) {
//            throw new WrongValuesPeselException("Invalid PESEL number!");
//        }
//        if (Character.getNumericValue(pesel.charAt(2)) > 1) {
//            throw new WrongValuesPeselException("Invalid PESEL number!");
//        }

        int checksum = (10 - (sum % 10)) % 10;
        if (checksum != Character.getNumericValue(pesel.charAt(10))) {
            throw new WrongValuesPeselException("Invalid PESEL number!");
        }

    }

    public char getGender(String pesel) {
        try {
            parse(pesel);
        } catch (WrongValuesPeselException e) {
            System.err.println(e.getMessage());
        }

        int genderDigit = Character.getNumericValue(pesel.charAt(9));
        return genderDigit % 2 == 0 ? 'K' : 'M';
    }

    public LocalDateTime getBirthDate(String pesel) throws DateTimeException {
        // parsowanie przed
        try {
            parse(pesel);
        } catch (WrongValuesPeselException e) {
            System.err.println(e.getMessage());
        }

        // Extract birth date from PESEL number if birthdate is before 2000 year

        int year = Integer.parseInt(pesel.substring(0, 2));
        int month = Integer.parseInt(pesel.substring(2, 4));
        int day = Integer.parseInt(pesel.substring(4, 6));
        // Adjust year and month based on century
        if (month > 20) {
            year += 2000;
            month -= 20;
        } else {
            year += 1900;
        }

        //31 luty - wyjątek
        LocalDateTime peselBirthDate = LocalDateTime.of(year, month, day, 0, 0);

        // Compare with input birth date and gender
        return peselBirthDate;
    }
}
