public class PrBev  {
    Beverage beverage;
    Integer orders;
    Double total_sell;


    public PrBev () {
	this.orders=0;
	this.total_sell=0.0;

    }

    public void pr(Beverage beverage) {
	this.beverage = beverage;
	this.orders+=1;
	this.total_sell+=beverage.cost();
	System.out.println("\n"+beverage.getDescription()
			   + " $" + beverage.cost());
    }

    public void totals()
    {

	System.out.println("\n\n************* Totals **************\n");
	System.out.println("orders:\t"+ orders +"\nSales: \t"+ total_sell +"\n");

    }
    
}