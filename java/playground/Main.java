public class Main {

    public static void main(String[] args) {
        Box b = new Box(1,2,3);
        b.add(3,4,5);
        for (int i=0; i<20; i=i+4)
            b.add(i,i+1,i+2,i+3);
        b.pr();
	System.out.println("\nSum: "+b.sum());




    }


}