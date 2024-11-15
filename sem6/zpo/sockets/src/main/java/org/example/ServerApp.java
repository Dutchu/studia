package org.example;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerApp extends Application {

    private Label statusLabel;
    private Circle circle;
    private ServerSocket serverSocket;
    private boolean serverRunning = false;
    private MenuItem startStopServerItem;
    private Thread serverThread;
    private Socket clientSocket;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Kółko - Serwer");

        circle = new Circle(50, javafx.scene.paint.Color.BLUE);
        Pane pane = new Pane(circle);
        double maxCircleRadius = 150.0;

        circle.centerXProperty().bind(pane.widthProperty().divide(2));
        circle.centerYProperty().bind(pane.heightProperty().divide(2));

        statusLabel = new Label("Serwer nie działa");

        MenuBar menuBar = new MenuBar();
        Menu menu = new Menu("Serwer");
        startStopServerItem = new MenuItem("Uruchom serwer");
        startStopServerItem.setOnAction(event -> toggleServer());
        menu.getItems().add(startStopServerItem);
        menuBar.getMenus().add(menu);

        BorderPane borderPane = new BorderPane();
        borderPane.setTop(menuBar);
        borderPane.setCenter(pane);
        borderPane.setBottom(statusLabel);

        primaryStage.setScene(new Scene(borderPane, 400, 400));
        primaryStage.show();
    }

    private void toggleServer() {
        if (serverRunning) {
            stopServer();
        } else {
            startServer();
        }
    }

    private void startServer() {
        serverRunning = true;
        Platform.runLater(() -> {
            statusLabel.setText("Serwer działa");
            startStopServerItem.setText("Zatrzymaj serwer");
        });

        serverThread = new Thread(() -> {
            try {
                serverSocket = new ServerSocket(12345);
                System.out.println("Server is running on port 12345...");

                while (serverRunning) {
                    try {
                        Socket newClientSocket = serverSocket.accept();

                        if (clientSocket != null && !clientSocket.isClosed()) {
                            PrintWriter out = new PrintWriter(newClientSocket.getOutputStream(), true);
                            out.println("Serwer jest zajęty");
                            newClientSocket.close();
                        } else {
                            clientSocket = newClientSocket;
                            Platform.runLater(() -> statusLabel.setText("Klient podłączony"));
                            BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

                            String line;
                            while ((line = in.readLine()) != null) {
                                double radius = Double.parseDouble(line.trim());
                                double finalRadius = Math.min(radius, 150.0);
                                Platform.runLater(() -> circle.setRadius(finalRadius));
                            }

                            Platform.runLater(() -> statusLabel.setText("Serwer działa"));
                            clientSocket = null;
                        }
                    } catch (Exception e) {
                        if (serverRunning) {
                            Platform.runLater(() -> statusLabel.setText("Serwer działa"));
                        }
                    }
                }
            } catch (Exception e) {
                Platform.runLater(() -> {
                    statusLabel.setText("Serwer nie działa");
                    e.printStackTrace();
                });
            }
        });
        serverThread.start();
    }

    private void stopServer() {
        serverRunning = false;
        Platform.runLater(() -> {
            statusLabel.setText("Serwer nie działa");
            startStopServerItem.setText("Uruchom serwer");
        });

        try {
            if (clientSocket != null && !clientSocket.isClosed()) {
                clientSocket.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            if (serverSocket != null && !serverSocket.isClosed()) {
                serverSocket.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (serverThread != null) {
            serverThread.interrupt();
        }
    }
}
