import java.util.ArrayList;
import java.util.List;


public class mArrayList {


    List<B> l = new ArrayList<B>();
    public static void main(String[] args) {
        mArrayList j = new mArrayList();
        j.run();
    }
    public void run() {
        l.add(new B("More"));
        l.add(new B("This"));
        l.add(new B("Time"));

        for (B i: l ){
            System.out.println(i.getS());
        }
    }


}