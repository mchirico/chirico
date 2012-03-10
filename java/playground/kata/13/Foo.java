public class Foo {

    public static void main(String[] args) {
	Foo f = new Foo();
	f.go(1,2,34);
    }
    public void go(int...x) {
	System.out.println("Length of x "+x.length);
	for(int i: x) {
	    System.out.println("i="+i);
	}
	int $stuff=0;
	System.out.println("Here stuff "+$stuff);
	
    }


}