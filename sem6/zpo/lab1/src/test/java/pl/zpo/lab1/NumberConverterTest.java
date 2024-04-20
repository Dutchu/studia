package pl.zpo.lab1;

import lombok.extern.java.Log;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.logging.Logger;

import static org.junit.Assert.*;

public class NumberConverterTest {

    private static final Logger LOG = Logger.getLogger(NumberConverter.class.getName());
    private NumberConverter nc;
    @Before
    public void setUp() throws Exception {
        LOG.info("Rozpoczynamy Testy");
        nc = new NumberConverter();
    }

    @After
    public void tearDown() throws Exception {
        LOG.info("Konczymy testy Testy");
    }

    @Test
    public void roman2arabic() {
        assertEquals("Assert if I is 1", 1, nc.roman2arabic("I"));
        assertEquals("Assert if I is 1", 5, nc.roman2arabic("V"));
        assertEquals("Assert if I is 1", 10, nc.roman2arabic("X"));
    }

    @Test
    public void arabic2roman() {
        fail("Niepowodzenie");
    }
}