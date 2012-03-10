//SequentialRun.java
import java.util.Map;
import java.util.HashMap;
public class SequentialRun extends AbstractRun {
    protected Map<String, Object> computeFinancials() {
        String lowPricedTicker = "";
        double lowPrice = Integer.MAX_VALUE;
        String highPricedTicker = "";
        double highPrice = Integer.MIN_VALUE;
        double netAssetValue = 0;
        for(int i = 0; i < Stocks.tickers.length; i++) {
            double price = YahooFinance.getPrice(Stocks.tickers[i]);
            netAssetValue += (price * Stocks.shares[i]);
            if(price < lowPrice) {
                lowPrice = price;
                lowPricedTicker = Stocks.tickers[i];
            }
            if(price > highPrice) {
                highPrice = price;
                highPricedTicker = Stocks.tickers[i];
            }
        }
        Map<String, Object> result = new HashMap<String, Object>();
        result.put("HIGHTICKER", highPricedTicker);
        result.put("HIGHPRICE", highPrice);
        result.put("LOWTICKER", lowPricedTicker);
        result.put("LOWPRICE", lowPrice);
        result.put("NAV", netAssetValue);
        return result;
    }
    public static void main(String[] args) throws Exception {
        new SequentialRun().computeFinancialsAndPrint();
    }
}


