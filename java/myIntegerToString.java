public class myIntegerToString {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java myIntegerToString 1 2 4");
            System.exit(0);
        }
        for (int i=0; i < args.length; ++i)
            System.out.println(Integer.valueOf(args[i]));

    }

}