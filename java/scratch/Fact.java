public class Fact {

    public static void main(String args[])
    {
        if (args.length < 1)
            return;

        int input = Integer.parseInt(args[0]);
        System.out.println("this is a test " + fact(input));
    }

    public static double fact(double x) {
        if (x < 1 )
            return 1;
        return fact(x-1)*x;
    }

}
