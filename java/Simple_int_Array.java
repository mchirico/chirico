public class Simple_int_Array {

    public static void main(String[] args) {
        int i[] = new int[3];

        i[0]=1;
        i[1]=1;
        i[2]=3;
        int count=0;
        for(int j: i) {
            System.out.println("i["+(count++)+"]= "+j);
	}
    }
}
