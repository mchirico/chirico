public class PassByReference {

    class Dog {
        private String name;
        private String lic;

        Dog() {

        }
        public void setName(String s) {
            name =s;
        }
        public void setLic(String s) {
            lic =s;
        }

        String getName() {
            return name;
        }
        String getLic() {
            return lic;
        }
    }

    public static void main(String argv[]) {
        new PassByReference().go();

    }

    void go() {
        Dog d = new Dog();
        myChange(d,"Bob","342");
        myPr(d);
    }

    void myChange(Dog d,String name, String lic) {
        d.setName(name);
        d.setLic(lic);
    }

    void myPr(Dog d) {
        System.out.println("Name: "+d.getName());
        System.out.println("Lic: "+d.getLic());
    }



}