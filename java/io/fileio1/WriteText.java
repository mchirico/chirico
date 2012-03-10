import java.io.*;
import java.util.*;
public class WriteText  {
    public static void main(String[] args) {
	try {
	    File f = new File (".","dataText");
	    PrintWriter o = new PrintWriter(new FileWriter(f));
	    o.println("example of text");
	    o.close();
	}
	catch (IOException e) { }
    }
}
