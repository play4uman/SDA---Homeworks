/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RMIServerPackage;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

/**
 *
 * @author Play4u
 */
public class RegisterWithRMIServer {
    @SuppressWarnings("CallToPrintStackTrace")
    public static void main(String[] args) {
        try{
            SudokuServerInterface stub = new ServerImplementation();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.rebind("Reg", stub);
            System.out.println("Success registering!");
        }
        catch(RemoteException ex){
            ex.printStackTrace();
        }
    }
    
}
