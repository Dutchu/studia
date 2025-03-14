package org.example;

import org.json.JSONObject;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class TimeClient extends JFrame {
    private static final int MULTICAST_PORT = 7;
    private static final String MULTICAST_ADDRESS = "225.4.5.6";
    private static final String DISCOVER_MESSAGE = "DISCOVER";

    // Communication state
    private Socket socket;
    private DatagramSocket discoverySocket;
    private PrintWriter out;
    private BufferedReader in;
    private String lastConnectedServer = null;
    private int lastConnectedPort = -1;
    private boolean connected = false;
    private final ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(2);
    private ScheduledFuture<?> discoveryTask;
    private ScheduledFuture<?> timeRequestTask;

    // Server discovery data
    private final Map<String, ServerInfo> discoveredServers = new ConcurrentHashMap<>();

    // UI components
    private JTextArea logArea;
    private JComboBox<String> serverComboBox;
    private JButton connectButton;
    private JButton disconnectButton;
    private JTextField queryIntervalField;
    private JButton updateServersButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            TimeClient client = new TimeClient();
            client.setVisible(true);
        });
    }

    public TimeClient() {
        setTitle("Time Client");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        initUI();

        // Start discovery process
        startServerDiscovery();
    }

    private void initUI() {
        // Main panel
        JPanel mainPanel = new JPanel(new BorderLayout());

        // Server selection panel
        JPanel serverPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        serverPanel.add(new JLabel("Available Servers:"));

        serverComboBox = new JComboBox<>();
        serverComboBox.setPreferredSize(new Dimension(250, 25));
        serverPanel.add(serverComboBox);

        updateServersButton = new JButton("Refresh");
        updateServersButton.addActionListener(e -> discoverServers());
        serverPanel.add(updateServersButton);

        connectButton = new JButton("Connect");
        connectButton.addActionListener(e -> connectToSelectedServer());
        serverPanel.add(connectButton);

        disconnectButton = new JButton("Disconnect");
        disconnectButton.setEnabled(false);
        disconnectButton.addActionListener(e -> disconnect());
        serverPanel.add(disconnectButton);

        mainPanel.add(serverPanel, BorderLayout.NORTH);

        // Query interval panel
        JPanel queryPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        queryPanel.add(new JLabel("Query Interval (ms):"));

        queryIntervalField = new JTextField("1000", 6);
        queryPanel.add(queryIntervalField);

        mainPanel.add(queryPanel, BorderLayout.CENTER);

        // Log area
        logArea = new JTextArea();
        logArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(logArea);
        mainPanel.add(scrollPane, BorderLayout.SOUTH);

        add(mainPanel);

        // Add window listener for cleanup on close
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                cleanup();
            }
        });
    }

    private void startServerDiscovery() {
        discoveryTask = scheduler.scheduleAtFixedRate(
                this::discoverServers, 0, 10, TimeUnit.SECONDS);
    }

    private void discoverServers() {
        // Clear old servers if not connected
        if (!connected) {
            discoveredServers.clear();
            updateServerComboBox();
        }

        try {
            // Send multicast DISCOVER message
            InetAddress group = InetAddress.getByName(MULTICAST_ADDRESS);
//            MulticastSocket socket = new MulticastSocket();
            // Ensure packets can cross routers
//            socket.setTimeToLive(32);
            discoverySocket = new DatagramSocket();
            discoverySocket.setSoTimeout(2000); // Set timeout for receiving responses
//            discoverySocket.setTimeToLive(32);


            byte[] msg = DISCOVER_MESSAGE.getBytes();
            DatagramPacket packet = new DatagramPacket(msg, msg.length, group, MULTICAST_PORT);
            discoverySocket.send(packet);

            // Client DISCOVER configuration
            log("Sent DISCOVER message from port: " + discoverySocket.getLocalPort());
            // Setup a separate thread to listen for OFFER responses
            scheduler.submit(this::listenForOffers);

        } catch (IOException e) {
            log("Error discovering servers: " + e.getMessage());
        }
    }

    private void listenForOffers() {
        try {
            byte[] buffer = new byte[1024];
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

            while (true) {
                try {
                    log("Waiting for Offer on port: " + discoverySocket.getLocalPort());
                    discoverySocket.receive(packet);
                    String message = new String(packet.getData(), 0, packet.getLength());
                    log(message);
                    processOfferMessage(message, packet.getAddress().getHostAddress());
                } catch (SocketTimeoutException e) {
                    break; // Stop listening after timeout
                }
            }

            if (!connected) {
                updateServerComboBox();
            }
        } catch (IOException e) {
            log("Error receiving server offers: " + e.getMessage());
        } finally {
            if (discoverySocket != null && !discoverySocket.isClosed()) {
                discoverySocket.close();
            }
        }
    }

    private void processOfferMessage(String message, String sourceIp) {
        try {
            JSONObject json = new JSONObject(message);

            if (json.getString("type").equals("OFFER")) {
                String address = json.getString("address");
                int port = json.getInt("port");

                // Skip localhost
                if (!address.equals("127.0.0.1")) {
                    ServerInfo serverInfo = new ServerInfo(address, port);
                    discoveredServers.put(address + ":" + port, serverInfo);
                    log("Discovered server: " + address + " on port " + port);
                }
            }
        } catch (Exception e) {
            log("Error processing offer message: " + e.getMessage());
        }
    }

    private void updateServerComboBox() {
        SwingUtilities.invokeLater(() -> {
            serverComboBox.removeAllItems();

            for (Map.Entry<String, ServerInfo> entry : discoveredServers.entrySet()) {
                String key = entry.getKey();
                serverComboBox.addItem(key);

                // Set the last connected server as selected
                if (lastConnectedServer != null &&
                        key.equals(lastConnectedServer + ":" + lastConnectedPort)) {
                    serverComboBox.setSelectedItem(key);
                }
            }
        });
    }

    private void connectToSelectedServer() {
        if (serverComboBox.getSelectedItem() == null) {
            log("No server selected");
            return;
        }

        String serverKey = serverComboBox.getSelectedItem().toString();
        ServerInfo serverInfo = discoveredServers.get(serverKey);

        if (serverInfo == null) {
            log("Invalid server selection");
            return;
        }

        // Get query interval
        int queryInterval;
        try {
            queryInterval = Integer.parseInt(queryIntervalField.getText().trim());
            if (queryInterval < 100) {
                queryInterval = 100; // Minimum interval
                queryIntervalField.setText("100");
            }
        } catch (NumberFormatException e) {
            log("Invalid query interval. Using default 1000ms.");
            queryInterval = 1000;
            queryIntervalField.setText("1000");
        }

        // Connect to server
        connectToServer(serverInfo.address, serverInfo.port, queryInterval);
    }

    private void connectToServer(String address, int port, int queryInterval) {
        disconnect(); // Disconnect if already connected

        try {
            log("Connecting to server: " + address + " on port " + port);

            socket = new Socket();
            socket.connect(new InetSocketAddress(address, port), 5000); // 5 second timeout

            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            connected = true;
            lastConnectedServer = address;
            lastConnectedPort = port;

            // Update UI
            SwingUtilities.invokeLater(() -> {
                connectButton.setEnabled(false);
                disconnectButton.setEnabled(true);
                updateServersButton.setEnabled(false);
            });

            log("Connected to server: " + address + " on port " + port);

            // Start time request thread
            timeRequestTask = scheduler.scheduleAtFixedRate(
                    () -> sendTimeRequest(System.currentTimeMillis()),
                    0,
                    queryInterval,
                    TimeUnit.MILLISECONDS
            );

            // Start listener thread for server responses
            scheduler.submit(this::listenForServerResponses);

        } catch (IOException e) {
            log("Connection error: " + e.getMessage());
            disconnect();

            // Restart server discovery
            discoverServers();
        }
    }

    private void sendTimeRequest(long clientTime) {
        if (connected && out != null) {
            try {
                JSONObject request = new JSONObject();
                request.put("type", "TIME_REQUEST");
                request.put("clientTime", clientTime);

                out.println(request.toString());
            } catch (Exception e) {
                log("Error sending time request: " + e.getMessage());
                disconnect();
            }
        }
    }

    private void listenForServerResponses() {
        try {
            String inputLine;
            while (connected && in != null && (inputLine = in.readLine()) != null) {
                final String response = inputLine;
                try {
                    JSONObject json = new JSONObject(response);

                    if (json.getString("type").equals("TIME_RESPONSE")) {
                        long serverTime = json.getLong("serverTime");
                        long clientTime = System.currentTimeMillis();
                        long roundTripTime = clientTime - lastSentTime;
                        long timeDiff = serverTime - (clientTime - roundTripTime/2);

                        final String logMessage = String.format(
                                "Server time: %d, Local time: %d, RTT: %d ms, Time difference: %d ms",
                                serverTime, clientTime, roundTripTime, timeDiff
                        );

                        SwingUtilities.invokeLater(() -> log(logMessage));
                    }
                } catch (Exception e) {
                    log("Error processing server response: " + e.getMessage());
                }
            }
        } catch (IOException e) {
            if (connected) {
                log("Server connection lost: " + e.getMessage());
                disconnect();
            }
        }
    }

    private long lastSentTime = 0;

    private void disconnect() {
        connected = false;

        // Cancel time request task
        if (timeRequestTask != null) {
            timeRequestTask.cancel(true);
            timeRequestTask = null;
        }

        // Close connection
        try {
            if (in != null) in.close();
            if (out != null) out.close();
            if (socket != null) socket.close();
        } catch (IOException e) {
            log("Error closing connection: " + e.getMessage());
        }

        in = null;
        out = null;
        socket = null;

        // Update UI
        SwingUtilities.invokeLater(() -> {
            connectButton.setEnabled(true);
            disconnectButton.setEnabled(false);
            updateServersButton.setEnabled(true);
        });

        // Restart discovery if disconnected
        if (!connected) {
            discoverServers();
        }
    }

    private void cleanup() {
        disconnect();

        if (discoveryTask != null) {
            discoveryTask.cancel(true);
        }

        scheduler.shutdownNow();
    }

    private void log(String message) {
        SwingUtilities.invokeLater(() -> {
            logArea.append(message + "\n");
            // Auto-scroll to bottom
            logArea.setCaretPosition(logArea.getDocument().getLength());
        });
    }

    // Helper class to store server information
    private static class ServerInfo {
        private final String address;
        private final int port;

        public ServerInfo(String address, int port) {
            this.address = address;
            this.port = port;
        }
    }
}