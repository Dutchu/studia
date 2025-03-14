package org.example.sync;

public class SynchronizedThreads {
    private static final Object lock = new Object();

    public static void start() {
        for (int i = 1; i <= 10; i++) {
            new LetterThread(i).start();
        }
    }

    static class LetterThread extends Thread {
        private final int threadId;
        private char currentLetter = 'A';

        public LetterThread(int threadId) {
            this.threadId = threadId;
        }

        @Override
        public void run() {
            while (true) {
                synchronized (lock) {
                    int suffix = (threadId == 10) ? 0 : threadId;
                    System.out.println(currentLetter + "" + suffix);
                    currentLetter = (currentLetter == 'Z') ? 'A' : (char) (currentLetter + 1);
                }
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    System.out.println("Wątek " + threadId + " został przerwany.");
                    break;
                }
            }
        }
    }
}