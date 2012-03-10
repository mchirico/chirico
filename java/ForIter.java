public class ForIter 
{
    String[] numbers = {"One", "Two", "Three" };

    public static void main(String[] args) {
	ForIter m = new ForIter();
	m.go();
    }

    public void go() {

	for (String i: numbers )
	    System.out.println(i);
    }

}