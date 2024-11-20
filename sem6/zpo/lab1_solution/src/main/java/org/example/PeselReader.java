package org.example;

import java.io.*;

public class PeselReader {

    private String fileName;
    private String sourceSuffix = ".txt";
    private String csvSuffix = ".csv";
    private String testDir = ".\\src\\test\\resources\\";

    public String read(String filePath) {
        this.fileName = filePath.split(".txt")[0];
        try {
            BufferedReader reader = new BufferedReader(new FileReader(fileName + sourceSuffix));
            PrintWriter writer = new PrintWriter(new File( testDir + fileName + csvSuffix));

            String line;
            while ((line = reader.readLine()) != null) {
                String[] numbers = line.split("\\s+");
                for (String number : numbers) {
                    writer.print(number);
                    writer.print(",");
                }
                writer.println();
            }

            reader.close();
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
