public class myMin {
    static int min(int firstArg, int... remainingArgs) {
        int min = firstArg;
        for (int arg : remainingArgs)
            if (arg < min)
                min = arg;
        return min;
    }

    public static void main(String[] args) {
        for (int i=0; i < args.length; ++i)
            System.out.println(Integer.valueOf(args[i]));
        System.out.println("min(3,12,4,9):="+min(3,12,4,9));
    }

}