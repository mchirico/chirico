package chirico.strategy;

public class MyMain0 {
    public static void main(String[] args) {

        Knight  knight = new Knight();
        Bishop  bishop = new Bishop();
        Scholar scholar = new Scholar();

        knight.display();
        knight.setFightBehavior(new Gun());
        knight.setVocalBehavior(new Talk());
        knight.performFight();
        knight.performVocal();

        bishop.display();
        bishop.setFightBehavior(new Condems());
        knight.setVocalBehavior(new Preach());
        bishop.performFight();
        knight.performVocal();
    }


}
