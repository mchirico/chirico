
public class Main {
    public static void main(String[] str) {
        Cell<Integer> c = new Cell<Integer>(0);
        Cell<Integer> p;
	Cell<Box> b = new Cell<Box>(new Box<String>("one"));
        p=c;

        for (int i=1; i<52; ++i){
            p.setNext(new Cell<Integer>(i));
            p=p.getNext();
        }
	long guess=50*51/2;

        p=c;
        long sum=0;
        while (p.getNext() != null) {

            sum+=p.getElement();
            p=p.getNext();

        }
        System.out.println("Element:"+sum+" Guess:"+guess);



    }

}