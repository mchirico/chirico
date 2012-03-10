public class Main {
    public static void main(String[] args) {
	A[] a = new A[10];
	for(int i=0; i < a.length; ++i)
	    {
		a[i] = new A();
		a[i].set_note("Example here: "+i);
	    }

	for(int i=0; i < a.length; ++i)
	    {
		pr(a[i]);
	    }
    }

    public static void pr(A a)
    {
	a.pr();
    }
}