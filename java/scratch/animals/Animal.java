abstract class Animal implements AnimalBehavior, AnimalInternalBehavior {
    void eat() {
	System.out.println("animal eating");
    }
}
