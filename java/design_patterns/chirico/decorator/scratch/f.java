class f {

    static int[] a = new int[20];

    public static void main(String[] args) {

	T t = new T();
	t.init(a);
	//t.pr();
	for(int i=0; i<20; ++i)
	    t.inc();
	t.pr();

    }

}