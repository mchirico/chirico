public class StarbuzzCoffee {
    public static void main(String args[]) {

	PrBev p = new PrBev();


	Beverage beverage = new Espresso();
	p.pr(beverage);


	Beverage beverage2 = new DarkRoast();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Whip(beverage2);
	p.pr(beverage2);

	p.totals();


    }
}