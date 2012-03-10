package chirico.strategy;

public class Scholar extends Soldier {

    public Scholar() {

        fightBehavior = new Spear();
        vocalBehavior = new Scream();
    }

    public void display() {
        System.out.println("I'm a Scholar");
    }
}
