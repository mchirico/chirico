package chirico.strategy;

public class Knight extends Soldier {

    public Knight() {

        fightBehavior = new Bow();
        vocalBehavior = new Silent();
    }

    public void display() {
        System.out.println("I'm a Knight");
    }
}
