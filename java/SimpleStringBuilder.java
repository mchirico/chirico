public class SimpleStringBuilder {

    public static void main(String[] args) {
	SimpleStringBuilder m = new SimpleStringBuilder();
	m.go();
    }
    
    public void go() {
	int[] data = {1,2,3,4};
	StringBuilder s = new StringBuilder("");
	for(int i = 0; i < data.length; ++i)
	    {
		s.append(data[i]);
		if (i < data.length - 1)
		    s.append(",");
	    }
	System.out.println(s);
    }

}