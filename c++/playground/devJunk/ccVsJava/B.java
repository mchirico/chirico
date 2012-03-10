public class B extends A {
    private C c;
    public B() {
        super("");
	System.out.println("B()");

    }

    public B(String name, Object value) {
        super(name,value);
        
    }
    public B(String name, C value) {
        super(name, value.toString());
        c= value;
    }
    public Object setValue(Object newValue) {
        Object retval = super.setValue(newValue);
        return retval;
    }
 

}
