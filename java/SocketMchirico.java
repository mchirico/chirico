import java.io.*;
import java.net.*;

public class SocketMchirico {

    public void go() {
        try {
	    //            Socket s = new Socket("74.125.113.121",80);
            Socket s = new Socket("localhost",1234);
            InputStreamReader streamReader = new InputStreamReader(s.getInputStream());
            BufferedReader reader = new BufferedReader(streamReader);
	    PrintWriter sout = new PrintWriter(s.getOutputStream(), true);
	    sout.write("GET HTTP/1.0\r\n");
	    sout.write("Connection: Keep-Alive\r\n");
	    sout.write("Accept: text/html\r\n\r\n");
	    System.out.println("here");
	    String servers = reader.readLine();
	    System.out.println(servers);
            reader.close();
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    public static void main(String[] args) {
        SocketMchirico  client = new SocketMchirico();
        client.go();
    }
}

