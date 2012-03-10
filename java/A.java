public class A {
    double a;
    static int count;

    public A() { a=0; count++; pr("A()"); }
    public A(int a) { this.a=a; count++; pr("Count:"+count); }
    public void setA(double a) {
	this.a=a;
    }
    public double getA() {
	return this.a;
    }
    public int getCount() {
	return count;
    }

    private void pr(String v) {
	System.out.println(v);
    }
}