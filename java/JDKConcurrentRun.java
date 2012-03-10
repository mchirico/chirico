//JDKConcurrentRun.java
import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
public class JDKConcurrentRun extends AbstractRun {
    String lowPricedTicker = "";
    double lowPrice = Integer.MAX_VALUE;
    String highPricedTicker = "";
    double highPrice = Integer.MIN_VALUE;
    double netAssetValue = 0;
    private synchronized void updateValues(final String ticker, final double
                                           value, final double price) {
        netAssetValue += value;
        if(price < lowPrice) {
            lowPrice = price;
            lowPricedTicker = ticker;
        }
        if(price > highPrice) {
            highPrice = price;
            highPricedTicker = ticker;
        }
    }
    protected Map<String, Object> computeFinancials() {
        ExecutorService service = Executors.newFixedThreadPool(100);
        final CountDownLatch latch = new CountDownLatch(Stocks.tickers.length);
        try {
            for(int i = 0; i < Stocks.tickers.length; i++) {
                final int index = i;
                service.execute(new Runnable() {
                    public void run() {
                        double price = YahooFinance.getPrice(Stocks.tickers[index]);
                        updateValues(
                            Stocks.tickers[index], Stocks.shares[index] * price, price);
                        latch.countDown();
                    }
                });
            }
            latch.await();
            Map<String, Object> result = new HashMap<String, Object>();
            result.put("HIGHTICKER", highPricedTicker);
            result.put("HIGHPRICE", highPrice);
            result.put("LOWTICKER", lowPricedTicker);
            result.put("LOWPRICE", lowPrice);
            result.put("NAV", netAssetValue);
            return result;
        } catch(Exception ex) {
            throw new RuntimeException(ex);
        } finally {
            service.shutdown();
        }
    }
    public static void main(String[] args) {
        new JDKConcurrentRun().computeFinancialsAndPrint();
    }
}

