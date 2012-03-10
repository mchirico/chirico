/**
  This program tries to read "Test.txt". If this file does
  not exist it is created and populated with data.



*/
import java.util.*;
import java.io.*;
public class MyReader {

    class CreateFile {
        CreateFile(String s) {
            try {
                File datafile = new File(".", s);
                RandomAccessFile f = new RandomAccessFile(datafile, "rw");
                f.seek(0);
                f.writeBytes("one\n");
                f.writeBytes("two\n");
                f.writeBytes("three\n");
                f.close();
            }
            catch (IOException e2) {
            }
        }
    }

    class ReadFile {
        ReadFile(String s) {
            try {
                File file = new File(".","Test.txt");
                BufferedReader reader = new BufferedReader(new FileReader(file));
                String line = null;
                while ((line= reader.readLine()) != null ) {
                    System.out.println(line);
                }

            } catch (Exception e) {

                CreateFile cf = new CreateFile(s);
                System.out.println("File Created. Running this again");
                ReadFile rf = new ReadFile(s);
                e.printStackTrace();
            }
        }
    }

    public void go() {
        ReadFile rf = new ReadFile("Test.txt");
    }

    public static void main(String[] args) {
        MyReader m = new MyReader();
        m.go();

    }



}