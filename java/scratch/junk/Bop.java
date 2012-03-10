public class Bop
{
    private int[] i={1,2,3,4,5};
    private static int c=0;
    private int count;
    private int a,b,d;


    public Bop() {
        c++;
    }



    public static int getc() {
        return c;
    }
    private void inc() {
        count++;
    }

    public static void setc(int c_in) {
        c=c_in;
    }





    public int geti(int i) {
        if (i < 0)
            return -1;
        if (i >= this.i.length )
            return -1;
        return this.i[i];
    }

}