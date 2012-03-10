public class PizzaSuper {
    public void prepare(){
	pr("Prepare");
    }
    public void bake() {
	pr("Bake");
    }
    public void box() {
	pr("Box");
    }
    private void pr(String s) {
	System.out.println(s);
    }

    

}