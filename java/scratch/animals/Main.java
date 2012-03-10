import java.util.*;
import java.io.*;

public class Main {
    ArrayList<Animal> v = new ArrayList<Animal>();

    public static void main(String[] args) {
	new Main().go();

	    }

    public void go() {
	System.out.println("This is example of go");
	fill_v();
	sounds_v(v);
    }

    public void fill_v() {
	v.add(new Dog());
	v.add(new Cat());
    }

    public void sounds_v(ArrayList<Animal> v) {
	System.out.println("Animal noises:");
	for(Animal a: v) {
	    System.out.print("\t");
	    a.noise();
	}

    }


}
