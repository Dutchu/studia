package org.example.async;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.util.List;
import java.util.concurrent.*;

public class AsyncTasksCancel extends JFrame {

    private JTextArea outputArea;
    private JTextField commandField;
    private JButton submitButton;
    private ScheduledExecutorService scheduler;
    private List<ScheduledFuture<?>> tasks;

    public AsyncTasksCancel() {
        super("Asynchroniczne zadania – kasowanie");
        setupGUI();
        initializeTasks();
        setupCommandHandling();
    }

    private void setupGUI() {
        outputArea = new JTextArea();
        outputArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(outputArea);

        commandField = new JTextField();
        submitButton = new JButton("Wyślij");

        JPanel inputPanel = new JPanel(new BorderLayout());
        inputPanel.add(commandField, BorderLayout.CENTER);
        inputPanel.add(submitButton, BorderLayout.EAST);

        setLayout(new BorderLayout());
        add(scrollPane, BorderLayout.CENTER);
        add(inputPanel, BorderLayout.SOUTH);

        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private void initializeTasks() {
        scheduler = Executors.newScheduledThreadPool(10);
        tasks = new ArrayList<>();

        for (int i = 1; i <= 10; i++) {
            int taskId = i;
            Runnable task = new AsyncTask(taskId);
            ScheduledFuture<?> future = scheduler.scheduleAtFixedRate(task, 0, 1, TimeUnit.SECONDS);
            tasks.add(future);
        }
    }

    private void setupCommandHandling() {
        ActionListener commandListener = new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String command = commandField.getText().trim();
                processCommand(command);
                commandField.setText("");
            }
        };

        submitButton.addActionListener(commandListener);
        commandField.addActionListener(commandListener);
    }

    private void processCommand(String command) {
        if (command.equalsIgnoreCase("exit")) {
            appendOutput("Kończenie programu...");
            scheduler.shutdownNow();
            System.exit(0);
        } else if (command.toLowerCase().startsWith("cancel")) {
            String param = command.substring("cancel".length()).trim();
            if (param.contains("-")) {
                String[] parts = param.split("-");
                try {
                    int start = Integer.parseInt(parts[0].trim());
                    int end = Integer.parseInt(parts[1].trim());
                    for (int j = start; j <= end; j++) {
                        cancelTask(j);
                    }
                } catch (NumberFormatException e) {
                    appendOutput("Błędny format liczb.");
                }
            } else {
                try {
                    int num = Integer.parseInt(param);
                    cancelTask(num);
                } catch (NumberFormatException e) {
                    appendOutput("Błędny numer zadania.");
                }
            }
        } else {
            appendOutput("Nieznana komenda. Użyj 'cancel x' lub 'cancel x-y' albo 'exit'.");
        }
    }

    private void cancelTask(int taskNumber) {
        if (taskNumber < 1 || taskNumber > tasks.size()) {
            appendOutput("Numer zadania musi być w zakresie 1-10.");
            return;
        }
        ScheduledFuture<?> future = tasks.get(taskNumber - 1);
        if (!future.isCancelled()) {
            boolean cancelled = future.cancel(true);
            appendOutput("Zadanie " + taskNumber + " anulowane: " + cancelled);
        } else {
            appendOutput("Zadanie " + taskNumber + " już zostało anulowane.");
        }
    }

    public void appendOutput(String text) {
        SwingUtilities.invokeLater(() -> {
            outputArea.append(text + "\n");
            outputArea.setCaretPosition(outputArea.getDocument().getLength());
        });
    }

    private class AsyncTask implements Runnable {
        private int taskId;
        private char letter;

        public AsyncTask(int taskId) {
            this.taskId = taskId;
            this.letter = 'A';
        }

        @Override
        public void run() {
            int suffix = (taskId == 10) ? 0 : taskId;
            String message = letter + "" + suffix;
            appendOutput(message);
            letter = (letter == 'Z') ? 'A' : (char)(letter + 1);
        }
    }

    public static void start() {
        SwingUtilities.invokeLater(() -> new AsyncTasksCancel());
    }
}
