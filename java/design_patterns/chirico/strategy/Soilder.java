package chirico.strategy;

public abstract class Soilder {
    FightBehavior fightBehavior;
    VocalBehavior vocalBehavior;

    public Soilder() {
    }

    public void setFightBehavior (FightBehavior fb) {
        fightBehavior = fb;
    }

    public void setVocalBehavior (VocalBehavior vb) {
        vocalBehavior = vb;
    }

    public void performFight() {
        fightBehavior.fight();
    }

    public void performVocal() {
        vocalBehavior.speak();
    }

    public void identifiesSelf() {

    }
}
