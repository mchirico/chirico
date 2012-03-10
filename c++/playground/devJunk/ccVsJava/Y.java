class Y extends X {
    protected int yMask = 0xff00;

    public Y() {
        System.out.println("Y()");
        System.out.printf("yMask %x\n\n",yMask);

        fullMask |= yMask;
    }
}
