/**
    This is new in Java 1.6 (Mustang)
 */
import java.io.File;
public class DiskFreeSpace 
{

    public static void main(String[] args) {
	DiskFreeSpace m = new DiskFreeSpace();
	m.go();
    }

    public void go() {
	File file = new File("/");
	long totalSpace = file.getTotalSpace();
	System.out.println("Total space on " + file + " = "
			   + totalSpace + " bytes");
    }

}