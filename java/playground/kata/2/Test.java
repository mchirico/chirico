
import java.util.regex.*;
public class Test {


    public static void main(String[] args) {
	Test t = new Test();

	t.go();
    }

    public void go() {
	int a = 5;
	Q q = new Q(3);
	t(a);
	q(q);
	prQ(q);
	System.out.println("Test here: " + a);

    }

    public void prQ(Q q) {
	System.out.println("Q is equal to: "+ q.getQ());
    }

    public void q(Q q) {
	q.setQ(299);
    }

    public void t(int i) {

	i=3;
    }
}