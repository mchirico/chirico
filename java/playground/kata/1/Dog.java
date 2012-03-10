class Dog {
    int size;
    String breed;
    String stuff;

    void bark() {
	System.out.println("Bark Bark");
    }
    void stats() 
    {
	pr("Size: ",size);
	pr("Breed: ",size);
	pr("Stuff: ",stuff);

    }


    private void pr(String t, int i) {
	if (i > 0)
	    System.out.println(t+i);
    }


    private void pr(String t, String s) {
	if (check(s))
	    System.out.println(t+s);
    }

    private boolean check(String s) {
	if (s == null ) 
	    return false;
	else
	    return true;
	       
    }

}