package org.example;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import javafx.scene.control.Slider;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientApp extends Application {

    private Label statusLabel;
    private Circle circle;
    private Socket socket;
    private PrintWriter out;
    private BufferedReader in;
    private boolean clientRunning = false;
    private MenuItem connectMenuItem;
    private Slider slider;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Kółko - Klient");

        circle = new Circle(50, javafx.scene.paint.Color.BLUE);
        Pane pane = new Pane(circle);

        // Place the circle in the center
        circle.centerXProperty().bind(pane.widthProperty().divide(2));
        circle.centerYProperty().bind(pane.heightProperty().divide(2));

        slider = new Slider(0, 150, 50);
        slider.valueProperty().addListener((obs, oldVal, newVal) -> {
            circle.setRadius(newVal.doubleValue());
            sendDataToServer(newVal.doubleValue());
        });

        statusLabel = new Label("Klient nie połączony");

        MenuBar menuBar = new MenuBar();
        Menu menu = new Menu("Połączenie z serwerem");
        connectMenuItem = new MenuItem("Połącz");
        connectMenuItem.setOnAction(event -> toggleConnection());
        menu.getItems().add(connectMenuItem);
        menuBar.getMenus().add(menu);

        BorderPane borderPane = new BorderPane();
        borderPane.setTop(menuBar);
        borderPane.setCenter(pane);
        borderPane.setBottom(statusLabel);
        borderPane.setRight(slider);

        primaryStage.setScene(new Scene(borderPane, 400, 400));
        primaryStage.show();
    }

    private void toggleConnection() {
        if (clientRunning) {
            disconnectFromServer();
        } else {
            connectToServer();
        }
    }

    private void connectToServer() {
        try {
            socket = new Socket("localhost", 12345);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            Platform.runLater(() -> {
                statusLabel.setText("Klient połączony");
                connectMenuItem.setText("Rozłącz");
                clientRunning = true;
            });

            new Thread(() -> {
                try {
                    while (clientRunning) {
                    }
                } catch (Exception e) {
                    Platform.runLater(() -> {
                        statusLabel.setText("Klient nie połączony");
                        connectMenuItem.setText("Połącz");
                    });
                    e.printStackTrace();
                }
            }).start();

        } catch (IOException e) {
            Platform.runLater(() -> {
                statusLabel.setText("Klient nie połączony");
                connectMenuItem.setText("Połącz");
            });
        }
    }

    private void sendDataToServer(double value) {
        if (clientRunning && out != null) {
            System.out.println("Sending data to server: " + value);
            out.println(value);
        } else {
            System.out.println("Nie można było połączyć się z serwerem.");
        }
    }

    private void disconnectFromServer() {
        clientRunning = false;
        Platform.runLater(() -> {
            statusLabel.setText("Klient nie połączony");
            connectMenuItem.setText("Połącz");
        });
        closeResources();
    }

    private void closeResources() {
        try {
            if (out != null) {
                out.close();
            }
            if (in != null) {
                in.close();
            }
            if (socket != null && !socket.isClosed()) {
                socket.close();
            }
            System.out.println("Połączenia zamknięte.");
        } catch (IOException e) {
            System.out.println("Błąd podczas zamykania połączenia: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
