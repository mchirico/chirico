public class MainBoat {

    static class Stuff {
	private int a,b,c;
	Stuff() { System.out.println("Stuff()"); }
	
    }


    public static void main(String[] args)
    {
	MainBoat m = new MainBoat();
	m.go();
    }
    public void go() {
	System.out.println("Test\n");
	Boat b = new Rowboat();
	Stuff s = new Stuff();
	
    }

}