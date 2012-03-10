import java.util.*;

public class MapTest {
    
    /**
     * @param args
     */
    public static void main(String[] args) {
	// TODO Auto-generated method stub
        MapTest p = new MapTest();
        p.doAction();
    }

    public void doAction() {
	System.out.println("This is a test");
	Map<String, Integer>  squares = new HashMap<String, Integer>( );
	squares.put("stuff",1);
	squares.put("stuff2",2);
	System.out.println(squares.get("stuff"));
	System.out.println(squares.keySet());
	for (Iterator<String> i = squares.keySet().iterator( ); i.hasNext( ); ) {
	    String s = i.next().toString();
	    System.out.println(s);
	}
	
	
    }
}
