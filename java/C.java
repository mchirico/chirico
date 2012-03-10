/*
  This shows that the base class will get instantiated before
  the calling calss.

*/

class A {
    A() {
        System.out.println("one");
    }
}
class B extends A {
    B() {
        System.out.println("two");
    }
}
public class C extends B{
    C() {
        System.out.println("three");
    }
    public static void main(String[] argv) {
        new C();
    }
}
