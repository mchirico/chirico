public class A {
    Dog d = new Dog();

    public static void main(String[] args) {

	A a = new A();
	a.go();

    }

    public void go() {
	d.bark();
	d.size = 34;
	d.breed = "Doberman";
	d.stats();
	
    }
    


}