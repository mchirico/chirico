class Fibonacci {
    /** Print out the Fibonacci sequence for values < 50 */
    public void m(String s) {
        int lo = 1;

        int hi = 1;

	System.out.println(lo);
	while (hi < 50) {
	    System.out.println(hi);
	    hi = lo + hi;       // new hi
	    lo = hi - lo;       /* new lo is (sum - old lo)
				   that is, the old hi */
	}
    }
}



class slop {
    public static void main(String[] args) {

        int SLOP_SIZE = 100;
        slop[] h = new slop[SLOP_SIZE];

        for(int i=0; i < SLOP_SIZE; ++i)
               h[i] = new slop();
        Fibonacci  f = new Fibonacci();
        f.m("test");
        System.out.println("After f.m()\n sqrt(3)="+Math.sqrt(3));


        for(int i=0; i < 3; ++i)
	    {
		for(int j=0; j < 10; ++j)
                     h[i].test(j);
	    }

    }

    public static void test(Integer i) {
        System.out.println("Test "+i);
    }

}
