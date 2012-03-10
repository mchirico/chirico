
import java.io.*;
public class Writer {
    File datafile;
    RandomAccessFile f;

    Writer(String s) {
        try {
            datafile = new File(".", s);
            f = new RandomAccessFile(datafile, "rw");
            // f.seek(0)
            // Here we go to the end
            f.seek(f.length());
        } catch ( Exception e) {

        }
    }
    public void pr(String s) {
        try {
            f.writeBytes(s+"\n");
        } catch (Exception e) {
            System.out.printf("Error in Writer.pr(String s) "+e);
        }
    }
    public void close() {
        try {
            f.close();

        } catch ( Exception e) {

        }

    }

}