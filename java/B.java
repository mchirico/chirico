public  class B {
    String s;
    static int count=0;
    /* Note B cannot have a type */
    B(String s) {
        this.s=s;
        count++;
    }
    public String getS() {
        return this.s;
    }
    public void setS(String s) {
        this.s = s;
    }
}


