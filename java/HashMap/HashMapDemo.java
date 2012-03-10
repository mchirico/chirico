import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class HashMapDemo {

    public static void main(String[] args) {
        HashMap<String, Box> hm = new HashMap<String, Box>();

        hm.put("Sue", new Box(23.34));
        hm.put("Tom", new Box(93.23));

        Set set = hm.entrySet();

        for (Iterator i = set.iterator(); i.hasNext();) {
            Map.Entry me = (Map.Entry) i.next();
            System.out.println("hm[" + me.getKey() + "]=" + ((Box) me.getValue()).getD());
            System.out.println("test");
        }

        // Add 100 to Sue's account
        Double balance = ((Box) hm.get("Sue")).getD();
        hm.put("Sue", new Box(balance + 100));

        System.out.println("Sue's new balance: " + hm.get("Sue").getD());
    }
}

