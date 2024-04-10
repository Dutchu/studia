import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class Main {
    public static void main(String[] args) {
        String url = "jdbc:oracle:thin:@localhost:1521/XE";
        String user = "SYSTEM";
        String password = "admin";

        // Create a Statement object from the connection
        Statement statement = connection.createStatement();

        // Define a SQL query to create a table
        String sql = "CREATE TABLE employees (" +
                "id INT PRIMARY KEY, " +
                "name VARCHAR(100), " +
                "email VARCHAR(100))";

        // Execute the SQL query
        statement.executeUpdate(sql);

        // Close the connection
        connection.close();

        System.out.println("Table created successfully");

        try {
            Connection connection = DriverManager.getConnection(url, user, password);
            System.out.println("Connected to the database!");
            connection.close();
        } catch (SQLException e) {
            System.out.println("Failed to connect to the database!");
            e.printStackTrace();
        }
    }
}