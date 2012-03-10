
import java.util.*;

public class Iter {


    public static void main(String[] args) {
        NavigableSet <R> ts = new TreeSet<R>();

        ts.add(new R());
        ts.add(new R());
        ts.add(new R(9));
        ts.add(new R(100));
        ts.add(new R(12));


        //Iterator i = ts.descendingIterator();
        Iterator i = ts.iterator();  // For ascending

        while (i.hasNext() )
        {
            R r = (R) i.next();
            System.out.println(r.getPriority());

        }


    }



}