class HuffyBike implements Bicycle, Horn {
    int speed;
    int Honk;
    public void changeSpeed(int newValue){
	speed=newValue;
    }
    public void changeSound(int newValue) {
	Honk=newValue;
    }

    public void show() {

	System.out.println("\n speed:\t"+speed
                           + "\n Hond:\t" + Honk);

    }

}