// Server component
package org.example;

import org.json.JSONObject;

import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class TimeServer {
    // Statistics tracking
    private final AtomicInteger connectedClients = new AtomicInteger(0);
    private final AtomicInteger disconnectedClients = new AtomicInteger(0);
    private final AtomicInteger discoverRequests = new AtomicInteger(0);
    private final ConcurrentHashMap<String, Integer> clientStats = new ConcurrentHashMap<>();

    // Server configuration
    private static final int MULTICAST_PORT = 7;
    private static final String MULTICAST_ADDRESS = "225.4.5.6";
    private static final String DISCOVER_MESSAGE = "DISCOVER";
    private static final int MIN_PORT = 10000;
    private static final int MAX_PORT = 65535;

    // Active server threads
    private final List<ServerThread> serverThreads = new ArrayList<>();
    private final ExecutorService threadPool = Executors.newCachedThreadPool();

    public static void main(String[] args) {
        TimeServer server = new TimeServer();
        server.start();
    }

    public void start() {
        try {
            // Get all network interfaces
            Enumeration<NetworkInterface> interfaces = NetworkInterface.getNetworkInterfaces();

            // Start a TCP server on each interface
            while (interfaces.hasMoreElements()) {
                NetworkInterface networkInterface = interfaces.nextElement();

                if (networkInterface.isUp() && !networkInterface.isLoopback() && !networkInterface.isVirtual()) {
                    Enumeration<InetAddress> addresses = networkInterface.getInetAddresses();

                    while (addresses.hasMoreElements()) {
                        InetAddress address = addresses.nextElement();

                        // Only use IPv4 addresses for simplicity
                        if (address instanceof Inet4Address) {
                            int randomPort = getRandomPort();
                            ServerThread serverThread = new ServerThread(address, randomPort);
                            serverThreads.add(serverThread);
                            threadPool.submit(serverThread);

                            System.out.println("Server started on interface: " +
                                    address.getHostAddress() + " port: " + randomPort);
                        }
                    }
                }
            }

            // Start the UDP multicast listener for DISCOVER messages
            startMulticastListener();

            // Start the statistics display thread
            startStatsDisplayThread();

        } catch (Exception e) {
            System.err.println("Error starting server: " + e.getMessage());
            e.printStackTrace();
        }
    }

    private int getRandomPort() {
        return MIN_PORT + new Random().nextInt(MAX_PORT - MIN_PORT);
    }

    private void startMulticastListener() {
        threadPool.submit(() -> {
            try {
                MulticastSocket socket = new MulticastSocket(MULTICAST_PORT);
                InetAddress group = InetAddress.getByName(MULTICAST_ADDRESS);
                socket.joinGroup(group);

                byte[] buffer = new byte[1024];

                while (true) {
                    DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
                    socket.receive(packet);

                    String receivedMessage = new String(packet.getData(), 0, packet.getLength());

                    if (receivedMessage.equals(DISCOVER_MESSAGE)) {
                        InetAddress clientAddress = packet.getAddress();

                        // Update statistics
                        discoverRequests.incrementAndGet();
                        String clientKey = clientAddress.getHostAddress();
                        clientStats.put(clientKey, clientStats.getOrDefault(clientKey, 0) + 1);

                        // Send OFFER response for each available server
                        for (ServerThread serverThread : serverThreads) {
                            String offerMessage = createOfferMessage(
                                    serverThread.getAddress().getHostAddress(),
                                    serverThread.getPort()
                            );

                            byte[] offerData = offerMessage.getBytes();
                            DatagramPacket offerPacket = new DatagramPacket(
                                    offerData,
                                    offerData.length,
                                    clientAddress,
                                    packet.getPort()
                            );

                            DatagramSocket datagramSocket = new DatagramSocket();
                            datagramSocket.send(offerPacket);
                            datagramSocket.close();
                        }
                    }
                }
            } catch (IOException e) {
                System.err.println("Multicast listener error: " + e.getMessage());
                e.printStackTrace();
            }
        });
    }

    private String createOfferMessage(String address, int port) {
        JSONObject json = new JSONObject();
        json.put("type", "OFFER");
        json.put("address", address);
        json.put("port", port);
        return json.toString();
    }

    private void startStatsDisplayThread() {
        threadPool.submit(() -> {
            while (true) {
                System.out.println("\n===== Server Statistics =====");
                System.out.println("Connected clients: " + connectedClients.get());
                System.out.println("Disconnected clients: " + disconnectedClients.get());
                System.out.println("DISCOVER requests: " + discoverRequests.get());
                System.out.println("Client activity:");

                for (Map.Entry<String, Integer> entry : clientStats.entrySet()) {
                    System.out.println(" - " + entry.getKey() + ": " + entry.getValue() + " requests");
                }

                try {
                    Thread.sleep(5000); // Update stats every 5 seconds
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        });
    }

    // Inner class to handle individual TCP server instances
    private class ServerThread implements Runnable {
        private final InetAddress address;
        private final int port;
        private ServerSocket serverSocket;

        public ServerThread(InetAddress address, int port) {
            this.address = address;
            this.port = port;
        }

        public InetAddress getAddress() {
            return address;
        }

        public int getPort() {
            return port;
        }

        @Override
        public void run() {
            try {
                serverSocket = new ServerSocket(port, 50, address);

                while (!Thread.currentThread().isInterrupted()) {
                    Socket clientSocket = serverSocket.accept();

                    // Create and start a new thread for the client
                    ClientHandler clientHandler = new ClientHandler(clientSocket);
                    threadPool.submit(clientHandler);
                }
            } catch (IOException e) {
                System.err.println("Server thread error on " + address.getHostAddress() +
                        ":" + port + " - " + e.getMessage());
            } finally {
                if (serverSocket != null && !serverSocket.isClosed()) {
                    try {
                        serverSocket.close();
                    } catch (IOException e) {
                        System.err.println("Error closing server socket: " + e.getMessage());
                    }
                }
            }
        }
    }

    // Inner class to handle individual client connections
    private class ClientHandler implements Runnable {
        private final Socket clientSocket;
        private final String clientAddress;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
            this.clientAddress = clientSocket.getInetAddress().getHostAddress();
            connectedClients.incrementAndGet();
            System.out.println("Client connected: " + clientAddress);
        }

        @Override
        public void run() {
            try (
                    BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                    PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true)
            ) {
                String inputLine;
                while ((inputLine = in.readLine()) != null) {
                    try {
                        JSONObject request = new JSONObject(inputLine);

                        if (request.getString("type").equals("TIME_REQUEST")) {
                            // Get current time in milliseconds
                            long serverTime = System.currentTimeMillis();

                            // Create and send response
                            JSONObject response = new JSONObject();
                            response.put("type", "TIME_RESPONSE");
                            response.put("serverTime", serverTime);

                            out.println(response.toString());

                            // Update client stats
                            clientStats.put(clientAddress, clientStats.getOrDefault(clientAddress, 0) + 1);
                        }
                    } catch (Exception e) {
                        System.err.println("Error processing client request: " + e.getMessage());
                    }
                }
            } catch (IOException e) {
                System.err.println("Client handler error: " + e.getMessage());
            } finally {
                disconnectedClients.incrementAndGet();
                connectedClients.decrementAndGet();

                try {
                    clientSocket.close();
                } catch (IOException e) {
                    System.err.println("Error closing client socket: " + e.getMessage());
                }

                System.out.println("Client disconnected: " + clientAddress);
            }
        }
    }
}