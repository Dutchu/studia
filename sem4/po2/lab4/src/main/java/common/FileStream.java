package common;

import java.io.*;
import java.util.stream.Collectors;

public class FileStream {

    private String fileName;

    public String getFileName() {
        return fileName;
    }

    public FileStream(String fileName) {
        this.fileName = fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public int writeFile(String message) {

        try (FileOutputStream file = new FileOutputStream(fileName);) {
            file.write(message.getBytes());

        } catch (IOException e) {

            e.printStackTrace();
            return 2;
        }

        return 1;
    }

    public byte[] readFile() {
        byte[] message = new byte[0];

        try (FileInputStream file = new FileInputStream(fileName);) {
            message = file.readAllBytes();

        } catch (IOException e) {
            e.printStackTrace();
        }

        return message;
    }

    public String readFileString() {

        String lines = "";

        try (FileReader fileReader = new FileReader(fileName)) {
            try (BufferedReader bufferedReader = new BufferedReader(fileReader)) {
                lines = bufferedReader.lines()
                        .collect(Collectors.joining(System.lineSeparator()));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return lines;
    }

    public String readLineString() {

        String line = "";

        try (FileReader fileReader = new FileReader(fileName)) {
            try (BufferedReader reader = new BufferedReader(fileReader)) {
                line = reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        return line;
    }

}
