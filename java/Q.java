
class Q3 {
    Q3() {
	System.out.println("three");
    }
}



class Q2 extends Q3 {
    Q2() {
	System.out.println("two");
    }
}


class Q1 extends Q2 {
    Q1() {
	System.out.println("one");
    }
}


public class Q extends Q1 {

    Q() {
	System.out.println("zero");
    }

    public static void main(String[] argv) {
        new Q();
    }


}