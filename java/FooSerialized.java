/**
   This is an example of implementing Serializable
*/

import java.io.*;
public class FooSerialized implements Serializable {

    private int a,b,c;

    public void setA(int val) {
	a=val;
    }
    public void setB(int val) {
	b=val;
    }
    public void setC(int val) {
	c=val;
    }

    public static void main(String[] args) {
	FooSerialized f = new FooSerialized();
	f.go();

	FooSerialized f2 = new FooSerialized();
	f2 = f.getSerial();
	f2.pr();

    }

    public void go() {
	setA(3);
	setB(12);
	setSerial();
    }
    public void pr() {

	System.out.println("A="+a);
	System.out.println("B="+b);
    }


    public void setSerial() {
	try {
	    FileOutputStream fs = new FileOutputStream("FooSerialized.ser");
	    ObjectOutputStream os = new ObjectOutputStream(fs);
	    os.writeObject(this);
	    os.close();
	} catch(Exception ex) {
	    ex.printStackTrace();
	}
    }

    public FooSerialized getSerial() {
	FooSerialized f = null;
	try {
	    ObjectInputStream is = new ObjectInputStream(new FileInputStream("FooSerialized.ser"));
	    f = (FooSerialized) is.readObject();
	} catch(Exception ex) {
	    ex.printStackTrace();
	}
	return f;



    }

    
}


