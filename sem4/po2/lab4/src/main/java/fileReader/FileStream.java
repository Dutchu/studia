package fileReader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileStream {

    private String fileName;

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public void writeFile(String message) {

        try (FileOutputStream file = new FileOutputStream(fileName);) {
            file.write(message.getBytes());

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
