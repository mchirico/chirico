import java.util.*;
public class Bucket<T> {
    private ArrayList<T> a;

    public void setB(ArrayList<T> val) {
	a=val;
    }
    public void pr() {
	for(Object i: a)
	    System.out.println("i="+i);
    }

}