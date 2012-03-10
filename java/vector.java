
import java.util.*;
class vector {
    Vector<Integer> vv =new Vector<Integer>();
    static int sale;
    static int count = 0;
    vector(int x, int y) {
        sale=x;
        count=y;
	vv.addElement(x);
	System.out.println(vv.elementAt(0));
    }

    public static void main(String[] argv) {
	vector q = new vector(1000,30);
        System.out.println(q.count);
    }
}
