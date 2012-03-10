public class Main {
    String file="Stuff";

    public static void main(String[] args) {
        Main m = new Main();
        m.go();
    }

    private void go() {
        Writer w = new Writer(file);
        for (int i=0; i<20; ++i)
            w.pr("Sample data "+i);
        w.close();

        System.out.printf("Date was written to %s\n",file);
    }

}