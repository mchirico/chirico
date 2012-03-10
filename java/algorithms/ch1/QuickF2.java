import java.util.*;
import java.io.*;

class QuickF2
{

    int id[],p,q,N;


    public static void main(String[] args)
    {
        QuickF2 m = new QuickF2();
        m.go();


    }

    public void go()
    {

        try {
            FileWriter fw = new FileWriter("Data.txt");
            fw.write("18\n");
            fw.write("\n3 4");
            fw.write("\n4 9");
            fw.write("\n8 0");
            fw.write("\n2 3");
            fw.write("\n5 6");
            fw.write("\n2 9");
            fw.write("\n5 9");
            fw.write("\n7 3");
            fw.write("\n4 8");
            fw.write("\n5 6");
            fw.write("\n0 2");
            fw.write("\n6 1");

            fw.close();

            FileReader fin = new FileReader("Data.txt");
            Scanner s = new Scanner(fin);
            if (s.hasNextInt()) {
                N = Integer.parseInt(s.next());
                id = new int[N];
                for (int i = 0; i < N ; i++) id[i] = i;
            } else {
                System.exit(-1);
            }

            System.out.println("Length: " + id.length);

            while (s.hasNextInt())
            {
                if (s.hasNextInt())
                    p= Integer.parseInt(s.next());
                if (s.hasNextInt()) {
                    q= Integer.parseInt(s.next());
                    int t = id[p];
                    if (id.length > q && t == id[q]){

			System.out.println("Connected: "+p+","+q);
                    }else {
                        for (int i=0; i < N; ++i)
                            if (id[i] == t) id[i] = id[q];

                        System.out.println("p="+p+" q="+q);
                    }

		    pr();

                }

            }

        } catch (IOException e)
        {
            System.out.println("Caught IOException");
        }
    }

    public void pr() {

	System.out.println("List:");
	for(int i = 0; i < id.length; ++i)
	    System.out.println("id["+i+"]="+id[i]);
    }
}


