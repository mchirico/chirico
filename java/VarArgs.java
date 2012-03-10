class Test {

    Test(String... s) {
        for (String i: s)
            System.out.println(i);
    }
}

public class VarArgs {

    public static void main(String[] args) {
        Test t = new Test("one","two");

    }

}