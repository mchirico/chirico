import java.util.regex.*;

/**
 * Simple example of using regex class.
 */
public class RESimple {
    public static void main(String[] argv) throws PatternSyntaxException {
        String pattern = "^Q[^u]\\d+\\.";
        String input = "QA777. is the next flight. It is on time.";

        Pattern p = Pattern.compile(pattern);

        boolean found = p.matcher(input).lookingAt( );

        System.out.println("'" + pattern + "'" +
			   (found ? " matches '" : " doesn't match '") + input + "'");
    }
}
