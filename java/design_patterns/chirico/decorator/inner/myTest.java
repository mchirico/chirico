public class myTest {
    private final static int SIZE = 10;
    private int[] arrayI = new int[SIZE];

    public myTest() {
	for(int i = 0; i < SIZE; ++i ) {
	    arrayI[i] = i;
	    System.out.println("arrayI[" + i + "]=" + arrayI[i]); 
	}
    }

    public static void main(String s[]) {
	myTest mt = new myTest();
    }
}
