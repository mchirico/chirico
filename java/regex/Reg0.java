import java.util.regex.*;
public class Reg0 {
    public static void main(String[] args) {

        Pattern p = Pattern.compile("[a-g]");
        Matcher m = p.matcher("One two three g ma");
        boolean b = false;
        while (b=m.find())
        {
            System.out.print(m.start()+ " ");
        }
    }
}
