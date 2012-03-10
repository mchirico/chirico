import java.util.*;
class Foo {

    public static void main(String[] args) {
	Foo f = new Foo();
	f.go();
	byte b=13;
	short s=3;

	System.out.println("Test "+f.j('a'));
	System.out.println(b);
    }
    public void go() {
	NavigableSet<Integer> ns = new TreeSet<Integer>();
	ns.add(10);
	ns.add(34);
	ns.add(2);
	ns.add(-1);

	Iterator dI = ns.descendingIterator();
	while(dI.hasNext()) {
	    System.out.println(dI.next());
	}
    }

    public byte j(int i) {
	return (byte) i;
    }
}