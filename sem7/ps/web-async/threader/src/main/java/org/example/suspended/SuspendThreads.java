package org.example.suspended;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class SuspendThreads extends JFrame {
    private JTextArea outputArea;
    private JTextField commandField;
    private JButton submitButton;
    private MyThread[] threads = new MyThread[10];

    public SuspendThreads() {
        super("Sterowanie Wątkami");
        setupGUI();
        initializeThreads();
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

    private void initializeThreads() {
        for (int i = 0; i < 10; i++) {
            int id = i + 1;
            threads[i] = new MyThread(id, outputArea);
            threads[i].start();
        }
    }

    private void setupCommandHandling() {
        ActionListener commandListener = new ActionListener() {
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
            System.exit(0);
        } else if (command.toLowerCase().startsWith("start")) {
            String param = command.substring(5).trim();
            handleCommand(param, true);
        } else if (command.toLowerCase().startsWith("stop")) {
            String param = command.substring(4).trim();
            handleCommand(param, false);
        } else {
            appendOutput("Nieznane polecenie. Użyj: 'start x', 'stop x' lub 'exit'.");
        }
    }

    private void handleCommand(String param, boolean start) {
        if (param.contains("-")) {
            String[] parts = param.split("-");
            try {
                int from = Integer.parseInt(parts[0].trim());
                int to = Integer.parseInt(parts[1].trim());
                for (int i = from; i <= to; i++) {
                    if (i >= 1 && i <= 10) {
                        if (start) {
                            threads[i - 1].resumeThread();
                        } else {
                            threads[i - 1].suspendThread();
                        }
                        appendOutput((start ? "Uruchomiono " : "Zatrzymano ") + "wątek " + i);
                    } else {
                        appendOutput("Numer wątku musi być w zakresie 1-10.");
                    }
                }
            } catch (NumberFormatException e) {
                appendOutput("Błędny format liczb.");
            }
        } else {
            try {
                int num = Integer.parseInt(param);
                if (num >= 1 && num <= 10) {
                    if (start) {
                        threads[num - 1].resumeThread();
                    } else {
                        threads[num - 1].suspendThread();
                    }
                    appendOutput((start ? "Uruchomiono " : "Zatrzymano ") + "wątek " + num);
                } else {
                    appendOutput("Numer wątku musi być w zakresie 1-10.");
                }
            } catch (NumberFormatException e) {
                appendOutput("Błędny numer.");
            }
        }
    }

    public void appendOutput(String text) {
        SwingUtilities.invokeLater(() -> {
            outputArea.append(text + "\n");
            outputArea.setCaretPosition(outputArea.getDocument().getLength());
        });
    }

    public static void start() {
        SwingUtilities.invokeLater(SuspendThreads::new);
    }
}
