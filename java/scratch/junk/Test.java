public class Test {

    public static void main(String s[])
    {
        Bop b = new Bop();
        Bop b2 = new Bop();
        b.setc(235);
        Stack stack = new Stack();
        stack.push(b);
        stack.push(b2);
        stack.push(new Bop());

        Bop p;
        p= (Bop) stack.pop();

        System.out.println("This is main: ("+p.getc()+")");
    }



}