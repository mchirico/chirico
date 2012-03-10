
import java.util.*;
public class Foo {
    MenuItem menuItem;
    static final int MAX_ITEMS = 6;
    ArrayList a = new ArrayList();
    

    public static void main(String[] args) {
	Foo f = new Foo();
	f.go();
    }
    public void go() {
	System.out.println("This is an example");
	menuItem = new MenuItem("Pizza","This is desc",false,3.23);
	pr();
    }

    public void pr() {
	System.out.println(menuItem.getName());
	System.out.println(menuItem.getDescription());
	System.out.println(menuItem.getPrice());
	if(menuItem.isVegetarian()) {
	    System.out.println("Yes Vegetarian");
	} else {
	    System.out.println("Not Vegetarian");
	}
    }
}