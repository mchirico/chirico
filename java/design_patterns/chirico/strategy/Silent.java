package chirico.strategy;

public class Silent implements  VocalBehavior  {
    public void speak() {
        System.out.println("Lips don't move");
    }
}
