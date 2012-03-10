
import java.io.*;
import java.util.*;

class Args2 {


static String[] MyRead(){
    String[] args = new String[10];
    int i = 0;

    try {
        BufferedReader in = 
                new BufferedReader(new InputStreamReader(System.in));

	do {
            System.out.print("> prompt ");
            args[i++]=in.readLine();
	} while (args[i-1].length() != 0 && i < 10);

    } catch (IOException e) {
    }

	return args;
}




    public static void main(String[] args) {

	System.out.println("This is your input on the command line:");
	for (int i = 0; i < args.length; ++i)
		System.out.println(args[i]);

	
	String[] args2 = MyRead();
	for (int i =0; i < args2.length && args2[i] != null; ++i) {
	    System.out.println("->"+args2[i]+"<-");
		}
	    
  }
}

