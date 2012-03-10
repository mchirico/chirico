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



class helloworld {
    public static void main(String[] args) {
        helloworld h0 = new helloworld();
        Fibonacci  f = new Fibonacci();
        f.m("test");
        System.out.println("After f.m()\n");
        for(int i=0; i < 10; ++i)
	    {
              h0.test(i);
	    }

    }

    public static void test(Integer i) {
        System.out.println("Test "+i);
    }

}
