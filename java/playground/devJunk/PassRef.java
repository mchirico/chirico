class PassRef {
    public static void main(String[] args) {
        Body sirius = new Body("Sirius", null);

        System.out.println("before: " + sirius);
        pr(sirius);
        commonName(sirius);
        System.out.println("after:  " + sirius);
        pr(sirius);
    }

    public static void commonName(Body bodyRef) {
        bodyRef.name = "Dog Star";
        bodyRef = null;
    }
    public static void pr(Body bodyRef) {
        System.out.println("Name: "+ bodyRef.name);
    }
}
