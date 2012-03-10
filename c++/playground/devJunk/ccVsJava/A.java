public class A {
    private final String name;
    private Object value = null;

    public A(String name) {
        this.name = name;
        System.out.println("A(String name)");
    }

    public A(String name, Object value) {
        this.name = name;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public Object getValue() {
        return value;
    }

    public Object setValue(Object newValue) {
        Object oldVal = value;
        value = newValue;
        return oldVal;
    }

    public String toString() {
        return name + "='" + value + "'";
    }
}
