
import java.util.*;
public class Foo {

    public static void main(String[] args) {
        Collection <Integer> hs1 = new HashSet<Integer>();
        hs1.add(3);
        hs1.add(10);
        hs1.add(23);
        hs1.add(55);

        Collection <Integer> hs2 = new HashSet<Integer>();
        hs2.add(2);
        hs2.add(10);
	hs2.add(23);

        Collection <Integer> intersect = hs1;
        boolean ok = intersect.retainAll(hs2);
        System.out.println("intersect: " + intersect);
    }

}