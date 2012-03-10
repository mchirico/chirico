import java.util.*;
import java.io.*;
public class FooMain {

    public static void main(String[] args) {
	FooMain f = new FooMain();
	f.go();
    }

    public void go() {
	try {
	    File file = new File("FooMain.txt");
	    Scanner s = new 
		Scanner(new FileReader(file)); //.useDelimiter("\\s*|\n");
	    while(s.hasNext()) {
		System.out.println(s.next());
	    }
	    s.close();

	    
	} catch(Exception e) {
	    e.printStackTrace();
	}
    }


}