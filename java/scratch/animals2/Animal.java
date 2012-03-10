abstract class Animal {

    AnimalBehavior animalBehavior;
    AnimalInternalBehavior animalInternalBehavior;

    public Animal() {
    }

    public void performEat() {
        animalBehavior.eat();
    }

    public void performNoise() {
        animalBehavior.noise();
    }
}
