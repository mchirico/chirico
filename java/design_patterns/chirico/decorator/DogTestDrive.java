class DogTestDrive {
    public static void main(String[] args) {
	int size=7;
	Dog[] pets = new Dog[size];

	for(int i=0; i < pets.length; ++i){
	    pets[i]= new Dog();
	    pets[i].set_size(i*i*i);
	    pets[i].set_name("Name "+i);
	}

	for(int i=0; i < pets.length; ++i) {
	    pets[i].bark();
	}
	
	/*
	pets = ne
one = new Dog();
	one.set_size(70);

	Dog two = new Dog();
	two.set_size(8);

	Dog three = new Dog();
	three.set_size(35);


	one.bark();
	two.bark();
	three.bark();
	*/
    }
}