import java.util.*;
public class Foo {
    public static void main(String[] args) {
	Set<Short> s = new HashSet<Short>();
	for(short i=0; i < 100;++i) {
	    s.add(i);
	    s.remove((short)(i-1));

	}

	System.out.println(s.size());

    }
}
