class P {
    static int sale;
    static int count = 0;
    P(int x, int y) {
        sale=x;
        count=y;
    }

    public static void main(String[] argv) {
	P q = new P(1000,30);
        System.out.println(q.count);
    }
}
