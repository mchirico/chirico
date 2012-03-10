package hash1;

import java.util.*;

public class H1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		HashMap<String, Double> hm = new HashMap<String, Double>();
		HashMap<String, Box>  hmB = new HashMap<String,Box>();
		
		hm.put("Sue", new Double(23.34));
		hm.put("Tom", new Double(93.23));
		hmB.put("Test",new Box(54.3));
		

		Set set = hm.entrySet();

		for (Iterator i = set.iterator(); i.hasNext();) {
			Map.Entry<String, Double> me = (Map.Entry<String, Double>) i.next();
			System.out.println("hm[" + me.getKey() + "]=" + me.getValue());
		}
		// Add 100 to Sue's account
		double balance = ((Double) hm.get("Sue")).doubleValue();
		hm.put("Sue", new Double(balance + 100));

		System.out.println("Sue's new balance: " + hm.get("Sue"));
		hmB.get("Test").incD(100.2);
		System.out.println("Value of hmB.get(\"Test\").getD():  "+ hmB.get("Test").getD());
		
		
	}

}
