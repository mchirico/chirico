import java.rmi.*;
public interface MyRemote extends Remote {
    public String sayHello() throws RemoteException;
}
