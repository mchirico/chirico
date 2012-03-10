import java.util.*;
public class Junk {

    public static void main(String[] args) {
	String[] s= { "one","two"};
	for(String i: s) 
	    System.out.println("i = "+i);



	System.out.println("Okay...doing this with ArrayList");
	ArrayList<String> v = new ArrayList<String>();
	v.add("Stuff");
	v.add("bubble");
	v.add("Pizza");
	v.add("Fresh Meat");
	for(String i: v) 
	    System.out.println("i = "+i);


	System.out.println("v.indexOf: "+v.indexOf("bubble9") );

	System.out.println("Now Object");

	Object[] o = v.toArray();
	for(Object i: o) 
	    System.out.println("o = "+i);



	
    }


}