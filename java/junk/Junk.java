import java.util.HashMap;
import java.util.Map;
public class Junk {

    protected Map<String, Object > M = new HashMap<String, Object> ();
    public void mygo() {
	String s= "test";
	String[] ss= {"one","two","three"};
	System.out.printf("This is a test %s\n",ss[0]);

	M.put("Test",new Integer(34));
	M.put("Test 2",new String("Stuff"));

    }


    public static void main(String[] args ) throws Exception {
        new Junk().mygo();


    }


}