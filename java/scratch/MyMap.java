import java.util.*;

class MyMap {
    public static void main(String args[])
    {
        Map<Integer, Integer> squares = new HashMap<Integer, Integer>();
        for (int i=0; i< 100; ++i) {
            squares.put(i,i*i);
        }
        for (int i=0; i< squares.size(); ++i)
        {
            System.out.println(i+"="+squares.get(i));
        }

        /*
          Need to finish
        for(Iterator<Integer> it = squares.keySet().iterator(); it.hasNext(); it.next())
            it.getValue();
        */
    }
}
