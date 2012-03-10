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
        Dog d = new Dog();
        d.setAnimalBehavior(new BigDogBehavior());
        v.add(d);
    }

    public void sounds_v(ArrayList<Animal> v) {
        for (Animal a: v) {
            System.out.print("Animal Talk:\t");
            a.performNoise();

            System.out.print("Eating Noise:\t");
            a.performEat();
        }

    }


}
