class Dog {
    private int size;
    private String name;


    Dog() {
	this.name="Lazy";

    }


    public void set_size(int size) {
	if (size > 3) {
	this.size=size;
	} else {
	    this.size=4;
	}
    }
    public void set_name(String name) {
	this.name=name;
    }
    
    public void bark() {
	System.out.println(name+": ");
	if (size > 60) {
	    System.out.println("Woof! Woo!");
	} else if (size > 14) {
	    System.out.println("Ruff! Ruff!");
	} else {
	    System.out.println("Yip! Yip!");
	}
    }
}
