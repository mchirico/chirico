import java.util.*;
import java.io.*;

class ScannerEx0
{
    public static void main(String[] args)
    {
	try {
	    FileWriter fw = new FileWriter("Data.txt");
	    fw.write("5 2 1");
	    fw.write("\n5 2 1");
	    fw.close();

	    FileReader fin = new FileReader("Data.txt");
	    Scanner s = new Scanner(fin);
	    while(s.hasNextInt())
		{
		    System.out.print(s.next() + " ");
		}
	} catch(IOException e)
	    {
		System.out.println("Caught IOException");
	    }
    }
}
