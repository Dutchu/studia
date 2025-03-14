package org.example;

public class FirstThread {
    private final static Runnable myTask = () -> System.out.println("Hello World!!");

    public static void start() {
        System.out.println("\n--- Program 1 – pierwszy wątek ---");

        var threadBuilder = Thread.ofPlatform();
        var thread = threadBuilder.start(myTask);

        try {
            thread.join();
            System.out.println("Thread has finished execution.");
        } catch (InterruptedException e) {
            System.err.println("Thread was interrupted.");
        }
    }
}
