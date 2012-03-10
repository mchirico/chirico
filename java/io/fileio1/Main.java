import java.io.*;
import java.util.*;
public class Main {
    public static void main(String[] args) {

	try {
	    File datafile = new File(".", "datafile");
	    RandomAccessFile f = new RandomAccessFile(datafile, "rw");
	f.seek(0);
	f.writeInt(2);
	f.close();
	} 
	catch(IOException e) {
	}


    }
}