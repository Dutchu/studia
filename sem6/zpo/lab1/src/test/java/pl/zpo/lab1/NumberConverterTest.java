package pl.zpo.lab1;

import lombok.extern.java.Log;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;
import org.junit.jupiter.params.provider.ValueSource;

import java.util.logging.Logger;

import static org.junit.jupiter.api.Assertions.*;

public class NumberConverterTest {

    private static final Logger LOG = Logger.getLogger(NumberConverter.class.getName());
    private NumberConverter nc;
    @BeforeEach
    public void setUp() throws Exception {
        LOG.info("Rozpoczynamy Testy");
        nc = new NumberConverter();
    }

    @AfterEach
    public void tearDown() throws Exception {
        LOG.info("Konczymy testy Testy");
    }

    @Test
    public void roman2arabic() {
        assertEquals( 1, nc.roman2arabic("I"), "Assert if I is 1");
        assertEquals(5, nc.roman2arabic("V"), "Assert if I is 1");
        assertEquals(10, nc.roman2arabic("X"), "Assert if I is 1");
    }

    @Test
    public void arabic2roman() {
        fail("Niepowodzenie");
    }

    @Test()
    public void roman2arabicException() {
        NumberFormatException thrown = assertThrows(NumberFormatException.class, () -> {
            nc.roman2arabic("ala");
        });
        assertEquals("Liczba nie jest znakiem rzymskim", thrown.getMessage());
    }

    @ParameterizedTest
//    @ValueSource(strings = {"'VII':7", "'MCMXCV':1995", "'MMX':2010"})
    @CsvSource({
            "VII, 7",
            "MCMXCV, 1995",
            "MMX, 2010"
    })
    public void roman2arabicExceptions(String input, int expected) {
        assertEquals(expected, nc.roman2arabic(input));
    }


}