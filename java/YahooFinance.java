//YahooFinance.java
//import java.util.*;
import java.net.URL;
import java.io.BufferedReader;
import java.io.InputStreamReader;
public class YahooFinance {
    public static double getPrice(final String ticker) {
        try {
            final URL url =
                new URL("http://ichart.finance.yahoo.com/table.csv?s=" + ticker);
            final BufferedReader reader =
                new BufferedReader(new InputStreamReader(url.openStream()));
            reader.readLine();
            final String data = reader.readLine();
	    System.out.println("Results of data: "+data);
            final String[] dataItems = data.split(",");
            return Double.parseDouble(dataItems[dataItems.length - 1]);
        } catch(Exception ex) {
            throw new RuntimeException(ex);
        }
    }
}
