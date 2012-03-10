class T
{
    private int[] p;


    public T() { p = null; }

    public long inc() {
	if( p == null || p.length == 0)
	    return 0;

        long sum=0;
	for(int i=0; i<p.length; ++i)
		{
		p[i]+=1;
	        sum+=p[i];
		}
	return sum;
    }

    public void pr() {
	if (p == null || p.length == 0)
	    return;

	for(int i=0; i<p.length; ++i)
	    {
	    System.out.println(p[i]);
	    p[i] +=1;
	    }


    }
    public void pr(int[] a) {
	for(int i=0; i<a.length; ++i)
	    System.out.println(a[i]);
    }
    public void init(int[] a) {
	for(int i=0; i<a.length; ++i)
	    a[i]=i;

	p = a;
    }

}