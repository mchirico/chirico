public class mArray {
    A[][] m = new A[9][4];

    public static void main(String[] args) {
        mArray m = new mArray();
        m.go();
    }

    public void go() {
        int c=0;
        for (int i=0; i<m.length; ++i)
        {
            for (int j=0; j<m[i].length; ++j)
            {
                m[i][j] = new A(c++);
                System.out.print(" ->"+m[i][j].getA()+" ");
            }
            System.out.println();
        }

        System.out.println("Count: "+m[0][0].getCount());


    }

}