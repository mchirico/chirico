
import java.util.*;
public class SimpleArray0 {

    public static void main(String[] args) {
        String s="stuff";
        char[] text = s.toCharArray();
        char[] c = new char[1000];



        System.arraycopy(text,0, c,0,text.length);
        // This scrambles everything up.
        Arrays.sort(text);
        System.out.println(c);
        System.out.println(text);




    }



}