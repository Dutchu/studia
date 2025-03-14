package org.example;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

import org.example.async.AsyncTasksCancel;
import org.example.suspended.SuspendThreads;
import org.example.sync.SynchronizedThreads;

public class Main {

    @FunctionalInterface
    interface Program {
        void execute();
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean exit = false;

        Map<Integer, Program> programMap = new HashMap<>();
        programMap.put(1, FirstThread::start);
        programMap.put(2, SuspendThreads::start);
        programMap.put(3, SynchronizedThreads::start);
        programMap.put(4, AsyncTasksCancel::start);
        programMap.put(5, () -> {
            System.out.println("Exiting the application. Goodbye!");
        });

        while (!exit) {
            displayMenu();
            System.out.print("Select an option (1-5): ");
            String input = scanner.nextLine();

            int option;
            try {
                option = Integer.parseInt(input);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a number between 1 and 5.\n");
                continue;
            }

            switch (option) {
                case 1, 2, 3, 4, 5 -> {
                    Program selectedProgram = programMap.get(option);
                    if (selectedProgram != null) {
                        selectedProgram.execute();
                        if (option == 5) {
                            exit = true;
                        } else {
                            System.out.println("\nPress Enter to return to the main menu...");
                            scanner.nextLine();
                        }
                    } else {
                        System.out.println("Option not implemented yet.\n");
                    }
                }
                default -> System.out.println("Invalid option. Please select a number between 1 and 5.\n");
            }
        }

        scanner.close();
    }

    private static void displayMenu() {
        System.out.println("===================================");
        System.out.println("      Multithreading Exercises     ");
        System.out.println("===================================");
        System.out.println("1. Program 1 – pierwszy wątek");
        System.out.println("2. Program 2 – ręczne wznawianie wątków");
        System.out.println("3. Program 3 – wykorzystanie synchronizacji");
        System.out.println("4. Program 4 – asynchroniczność");
        System.out.println("5. Exit");
        System.out.println("-----------------------------------");
    }
}