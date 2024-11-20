package org.example;

import org.example.WatekCzytajacy;

import java.util.*;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class SharedBuffer {
    private static final BlockingQueue<String> buffer = new ArrayBlockingQueue<>(1);
    private static final AtomicInteger finishedProducers = new AtomicInteger(0);
    private static final int totalProducers = 3;
    private static final Lock lock = new ReentrantLock();
    private static final Condition producerCondition = lock.newCondition();
    private static WatekCzytajacy currentProducer;


    private static final List<WatekCzytajacy> producers = new ArrayList<>();
    private static int sequenceIndex = 0;

    public static BlockingQueue<String> getBuffer() {
        return buffer;
    }

    public static Lock getLock() {
        return lock;
    }

    public static Condition getProducerCondition() {
        return producerCondition;
    }

    public static void addProducerToList(WatekCzytajacy producer) {
        lock.lock();
        try {
            producers.add(producer);
            if (currentProducer == null) {
                currentProducer = producers.get(sequenceIndex);
            }
            System.out.println("[SharedBuffer] Added producer to list: " + producer.getFileName());
            producerCondition.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public static boolean isMyTurn(WatekCzytajacy producer) {
        lock.lock();
        try {
            return currentProducer == producer;
        } finally {
            lock.unlock();
        }
    }

    public static void switchToNextProducer() {
        lock.lock();
        try {
            sequenceIndex++;
            if (sequenceIndex < producers.size()) {
                currentProducer = producers.get(sequenceIndex);
            } else {
                currentProducer = null;
            }
            System.out.println("[SharedBuffer] Switched to the next producer: " + (currentProducer != null ? currentProducer.getFileName() : "None"));
            producerCondition.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public static void producerFinished() {
        lock.lock();
        try {
            finishedProducers.incrementAndGet();
            System.out.println("[SharedBuffer] Producer finished work. Remaining producers: " + (totalProducers - finishedProducers.get()));
            if (isAllProducersFinished()) {
                System.out.println("[SharedBuffer] All producers have finished. Notifying consumer.");
                producerCondition.signalAll();
            }
        } finally {
            lock.unlock();
        }
    }

    public static boolean isAllProducersFinished() {
        return finishedProducers.get() == totalProducers;
    }
}
