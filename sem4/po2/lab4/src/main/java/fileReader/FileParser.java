package fileReader;

public class LineParser {

    public String getMessage(String fileName) {

        String message = null;
        byte[] byteMessage;
        FileStream fileStream =  new FileStream(fileName);
        byteMessage = fileStream.readFile();

        for (byte b : byteMessage) {
            System.out.printf("%c ", b);
        }
        return message;
    }
}
