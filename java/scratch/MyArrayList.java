import java.util.*;
import java.io.*;
public class MyArrayList {
    ArrayList<String> sList = new ArrayList<String>();


    public static void main(String[] args) {
        new MyArrayList().go();
    }

    public void go() {
        getList();
        System.out.println(sList);
        Collections.sort(sList);
        System.out.println(sList);
    }



    void getList() {
        try {
            File file = new File("slist.txt");
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line = null;
            while ((line = reader.readLine()) != null) {
                addS(line);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    void addS(String lineToParse) {
        String[] tokens = lineToParse.split("/");
        sList.add(tokens[0]);
    }
}
