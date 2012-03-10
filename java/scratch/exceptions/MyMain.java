public class MyMain {

    public static void main(String[] args){
	System.out.println("Test");
	try {
	new MyMain().go();
	} catch (Wow e) {
	    System.out.println("This is: "+e);
	}
    }

    public void go() throws Wow
    {
	throw new Wow("stuff");

    }
}