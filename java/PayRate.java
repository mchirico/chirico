import java.util.*;




public class PayRate {

    class CalTax {
	double employerFICA = 0.0765;
	double employeeFICA = 0.0765;
	double merchantTAX = 0.01; // Local township tax;
	double wageTax = 0.01;
	double stateTax = 0.06;
	double federalTax = 0.22;
	double totalEstimate = 0;
	double estimateTaxPct = 0.34;
	double Gross = 0;

	CalTax(double Gross) {
	    this.Gross= Gross;
	    totalEstimate = Gross * estimateTaxPct;

	}

	   

    }





    public static void main(String[] args) {

        new Main().go();
    }

    public void go() {
        Scanner in = new Scanner(System.in);


        System.out.print("What is your name? ");
        String name = in.nextLine();
        System.out.print("What is your hourly rate? ");
        double rate = in.nextDouble();
        System.out.print("How many hours did you work today? ");
        double hrs = in.nextDouble();
        System.out.println("Report for "+ name);
        System.out.println("Today you made "+ Double.toString(rate*hrs) );
        System.out.println("Weekly "+ Double.toString(rate*hrs*5) );
        System.out.println("Year "+ Double.toString(rate*hrs*5*50) );
        System.out.println("Taxes "+ Double.toString(0.28*rate*hrs*5*50) );
        System.out.println("Expenses "+ Double.toString(0.03*rate*hrs*5*50) );

	
    }
}