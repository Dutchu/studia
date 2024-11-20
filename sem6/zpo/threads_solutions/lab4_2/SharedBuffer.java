package org.example;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class SharedBuffer {
    private static final BlockingQueue<Character> buffer = new ArrayBlockingQueue<>(1); // Bufor jednoelementowy dla znaków
    private static final AtomicInteger finishedProducers = new AtomicInteger(0);
    private static final int totalProducers = 3; // Liczba producentów

    public static BlockingQueue<Character> getBuffer() {
        return buffer;
    }

    public static void producerFinished() {
        finishedProducers.incrementAndGet();
    }

    public static boolean isAllProducersFinished() {
        return finishedProducers.get() == totalProducers;
    }
}
