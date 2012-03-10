package chirico.strategy;

public class Bishop extends Soldier {

    public Bishop() {

        fightBehavior = new Condems();
        vocalBehavior = new Silent();
    }

    public void display() {
        System.out.println("I'm a Bishop");
    }
}
