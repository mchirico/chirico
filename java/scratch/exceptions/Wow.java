public class Wow extends Exception {
    public final String attrName;

    public Wow(String name) {
        super("No attribute named \"" + name + "\" found");
        attrName = name;
    }
}
