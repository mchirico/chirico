import java.util.*;
import java.io.*;




public class R implements Comparable {
    private static final String FILE="bubble";
    private static int count=0;
    private int priority;

    public R() {
        priority = count++;
    }
    public R(int p) {
        priority = p;
    }

    public int getPriority() {
        return priority;
    }

    public int compareTo(Object anotherR) throws ClassCastException {
        if (!( anotherR instanceof R))
            throw new ClassCastException("An R object expected.");
        int anotherRpriority = ((R) anotherR).getPriority();
        return this.priority - anotherRpriority;
    }

}