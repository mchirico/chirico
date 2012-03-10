public class A implements Verbose {

    int LEVEL=0;


    public static void main(String[] args) {
	A a = new A();
	a.go();

    }

    public void go() {
	System.out.println("Test here");
	setVerbosity(TERSE);
	System.out.println(getVerbosity());
    }

    public void setVerbosity(int level){
	LEVEL = level;
    }
    public int getVerbosity() {
	return LEVEL;
    }



}