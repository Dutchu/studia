package org.example;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

import java.util.logging.Logger;

import static org.junit.jupiter.api.Assertions.*;

class PeselParserTest {

    private PeselParser parser;
    private static final Logger LOG =  Logger.getLogger(PeselParser.class.getName());

    @org.junit.jupiter.api.BeforeEach
    public void setUp() {
        parser = new PeselParser();
    }

    @org.junit.jupiter.api.AfterEach
    void tearDown() {
    }


    @ParameterizedTest
    @CsvFileSource(resources = "/pesele.csv", numLinesToSkip = 0)
    void parse(String pesel) {
        assertTrue(parser.parse(pesel));
    }

    @Test
    void parseThrowsExceptionForInvalidFormat() {
        assertThrows(IllegalArgumentException.class, () -> parser.parse("invalidFormat"));
    }

    @Test
    void parseReturnsTrueForValidPesel() {
        assertTrue(parser.parse("97041123252"));
    }

    @Test
    void parseReturnsFalseForInvalidPesel() {
        assertFalse(parser.parse("97041123253")); // invalid PESEL but in correct format
    }

    @Test
    void getGenderReturnsCorrectGender() {
        assertEquals('M', parser.getGender("97041123252")); // male PESEL
        assertEquals('K', parser.getGender("97041223252")); // female PESEL
    }

    @Test
    void validateReturnsTrueForCorrectBirthDateAndGender() {
        assertTrue(parser.validate("97041123252", "1997-04-11", 'M')); // male, birth date: 1997-04-11
    }
}