import java.util.*;

public class HashMapDemo {

    public static void main(String[] args) {
        HashMap<String,Double> hm = new HashMap<String,Double>();

        hm.put("Sue", new Double(23.34));
        hm.put("Tom", new Double(93.23));

        Set set = hm.entrySet();

        for (Iterator i = set.iterator(); i.hasNext(); ) {
            Map.Entry me = (Map.Entry)i.next();
            System.out.println("hm["+me.getKey() + "]="+me.getValue());
        }

        // Add 100 to Sue's account
        double balance = ((Double)hm.get("Sue")).doubleValue();
        hm.put("Sue", new Double(balance + 100));

        System.out.println("Sue's new balance: " + hm.get("Sue"));
    }
}
