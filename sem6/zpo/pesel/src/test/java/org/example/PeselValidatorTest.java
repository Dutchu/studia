package org.example;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

import java.time.LocalDateTime;
import java.util.logging.Logger;

import static org.junit.jupiter.api.Assertions.*;

class PeselValidatorTest {

    private PeselValidator parser;
    private static final Logger LOG =  Logger.getLogger(PeselValidator.class.getName());

    @org.junit.jupiter.api.BeforeEach
    public void setUp() {
        parser = new PeselValidator();
    }

    @org.junit.jupiter.api.AfterEach
    void tearDown() {
    }


    @ParameterizedTest
    @CsvFileSource(resources = "/pesele.csv", numLinesToSkip = 0)
    void parse(String pesel) {
        assertDoesNotThrow(() -> parser.parse(pesel), "Should not throw any Errors");
    }

    @Test
    void parseThrowsWrongPeselFormatException() {
        assertThrows(WrongValuesPeselException.class, () -> parser.parse("97041223252"));
        assertThrows(WrongValuesPeselException.class, () -> parser.parse("97041123253"));
    }

    @Test
    void getGenderReturnsCorrectGender() {
        assertEquals('M', parser.getGender("97041123252")); // male PESEL
        assertEquals('K', parser.getGender("97041223252")); // female PESEL
    }

    @Test
    void validateReturnsTrueForCorrectBirthDateAndGender() {
        assertEquals(parser.getBirthDate("97041123252"), LocalDateTime.of(1997, 4, 11, 0, 0), "Should return correct birth date."); // male, birth date: 1997-04-11
    }
}