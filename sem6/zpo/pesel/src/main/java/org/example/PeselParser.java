package org.example;

public class PeselParser {

    public boolean parse(String pesel) {
        if (pesel == null || pesel.length() != 11) {
            return false;
        }

        int[] weights = {1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
        int sum = 0;

        for (int i = 0; i < weights.length; i++) {
            sum += weights[i] * Character.getNumericValue(pesel.charAt(i));
        }

        int checksum = (10 - (sum % 10)) % 10;
        return checksum == Character.getNumericValue(pesel.charAt(10));
    }

    public char getGender(String pesel) {
        if (parse(pesel)) {
            int genderDigit = Character.getNumericValue(pesel.charAt(9));
            return genderDigit % 2 == 0 ? 'K' : 'M';
        } else {
            throw new IllegalArgumentException("Invalid PESEL number");
        }
    }

    public boolean validate(String pesel, String birthDate, char gender) {
        if (!parse(pesel)) {
            throw new IllegalArgumentException("Invalid PESEL number");
        }

        // Extract birth date from PESEL number
        String year = pesel.substring(0, 2);
        String month = pesel.substring(2, 4);
        String day = pesel.substring(4, 6);
        String peselBirthDate = "19" + year + "-" + month + "-" + day;

        // Extract gender from PESEL number
        char peselGender = getGender(pesel);

        // Compare with input birth date and gender
        return peselBirthDate.equals(birthDate) && peselGender == gender;
    }
}
