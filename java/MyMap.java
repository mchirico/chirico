import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
public class MyMap {

    public static void main(String[] args) {

        new MyMap().go();
    }

    public void go() {
        Map<String, Long> map = new HashMap<String, Long>();
        map.put("One",34L);
        map.put("Two",45L);


        Set s=map.entrySet();

        //Move next key and value of Map by iterator
        Iterator it=s.iterator();

        while(it.hasNext())
        {
            // key=value separator this by Map.Entry to get key and value
            Map.Entry m =(Map.Entry)it.next();

            // getKey is used to get key of Map
            String key=(String)m.getKey();

            // getValue is used to get value of key in Map
            Long value=(Long)m.getValue();

            System.out.println("Key :"+key+"  Value :"+value);
        }


    }
}