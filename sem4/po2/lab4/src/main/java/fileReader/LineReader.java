package fileReader;

import java.io.File;
import java.io.FileNotFoundException;
import java.net.URL;
import java.util.Scanner;

public class LineReader {

    private final String fileName;
    private static Scanner sc = null;

    public LineReader(String fileName) {
        this.fileName = fileName;
    }

    public String readLine() {

        URL url = getClass().getResource(fileName);
        File file = new File(url != null ? url.getPath() : "");

        try {
            sc = new Scanner(file);
        } catch (FileNotFoundException e) {
            System.err.println(e.getMessage());
        }

        if (sc == null) {
            System.err.println("[ ERROR : fileReader.LineReader.readLine() ] Couldn't read a file");
            return "";
        }

        return sc.nextLine();
    }
}
