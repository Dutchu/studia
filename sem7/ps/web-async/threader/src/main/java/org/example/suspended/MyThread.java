package org.example.suspended;

import javax.swing.*;

class MyThread extends Thread {
    private volatile boolean suspended = true;
    private final int threadId;
    private final JTextArea outputArea;

    public MyThread(int threadId, JTextArea outputArea) {
        this.threadId = threadId;
        this.outputArea = outputArea;
    }

    public void suspendThread() {
        suspended = true;
    }

    public synchronized void resumeThread() {
        suspended = false;
        notify();
    }

    private void appendOutput(String text) {
        SwingUtilities.invokeLater(() -> {
            outputArea.append(text + "\n");
            outputArea.setCaretPosition(outputArea.getDocument().getLength());
        });
    }

    @Override
    public void run() {
        char letter = 'A';
        while (true) {
            synchronized (this) {
                while (suspended) {
                    try {
                        wait();
                    } catch (InterruptedException e) {
                        appendOutput("Wątek " + threadId + " został przerwany.");
                        return;
                    }
                }
            }
            int idSuffix = (threadId == 10) ? 0 : threadId;
            appendOutput(letter + "" + idSuffix);
            letter++;
            if (letter > 'Z') {
                letter = 'A';
            }
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                appendOutput("Wątek " + threadId + " przerwany podczas snu.");
                return;
            }
        }
    }
}