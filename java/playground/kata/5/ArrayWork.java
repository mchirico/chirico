
import java.util.*;
public class ArrayWork {

    public static void main(String[] args) {
	ArrayWork a = new ArrayWork();
	a.go();
    }

    public void go() {
	Bucket<String> b = new Bucket<String>();
	ArrayList<String> s = new ArrayList<String>();
	s.add("one");
	s.add("two");
	s.add("three");
	b.setB(s);

	double x = 5*Math.random();
	for(int i = 0; i <= (int) x; ++i) 
	    s.add("  ("+i+") ");

	s.add("Is it Link or Copy? Hint: If you see this it's copy");
	b.pr();
    }
}