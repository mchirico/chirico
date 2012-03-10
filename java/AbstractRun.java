//AbstractRun.java
import java.util.Map;
public abstract class AbstractRun {
    protected abstract Map<String, Object> computeFinancials();
    public void computeFinancialsAndPrint() {
        final long start = System.nanoTime();
        Map<String, Object> result = computeFinancials();
        final long end = System.nanoTime();
        System.out.printf("High priced stock is %s at price $%.2f\n",
                          result.get("HIGHTICKER"), result.get("HIGHPRICE"));
        System.out.printf("Low priced stock is %s at price $%.2f\n",
                          result.get("LOWTICKER"), result.get("LOWPRICE"));
        System.out.printf("Net Asset Value is $%.2f\n", result.get("NAV"));
        System.out.printf("Time taken %.2f seconds\n", (end - start)/1.0e9);
    }
}

