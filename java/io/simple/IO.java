import java.util.*;
import java.io.*;
class IO {


    public static void main(String[] args) {
        try {
            FileWriter fw = new FileWriter("Text.txt");
            for (int i=0; i < 200; ++i)
            {
                String s = String.format("(%d)\n",i);
                fw.write(s);

            }
            fw.close();


        }catch (IOException e)
        {
	    System.out.println("Error writing to file\n");

        }

    }



}