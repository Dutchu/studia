package pl.zpo.lab1;

import java.util.HashMap;
import java.util.Map;

public class NumberConverter {
    public int roman2arabic(String roman) {
        Map<Character, Integer> romanValues = new HashMap<>();
        romanValues.put('I', 1);
        romanValues.put('V', 5);
        romanValues.put('X', 10);
        romanValues.put('L', 50);
        romanValues.put('C', 100);
        romanValues.put('D', 500);
        romanValues.put('M', 1000);

        int result = 0;
        int lastValue = 0;
        for (int i = roman.length() - 1; i >= 0; i--) {
            int value = romanValues.get(roman.charAt(i));
            if (value >= lastValue) {
                result += value;
            } else {
                result -= value;
            }
            lastValue = value;
        }
        return result;
    }
    public String arabic2roman(String roman) {
        return null;
    }
}
