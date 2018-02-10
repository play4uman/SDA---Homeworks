/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RMIServerPackage;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 *
 * @author Play4u
 */
public class ServerImplementation extends UnicastRemoteObject implements SudokuServerInterface{
    SolIter generator;
    
    public ServerImplementation ()throws RemoteException{
        generator = new SolIter();
    }
    
    @Override
    public int[][] generateAndPassSudoku() throws RemoteException{
          return generator.getAnswer();
    }

    @Override
    public int[][] showResult(boolean correctlyAnswered) throws RemoteException{
        if (!correctlyAnswered)
            return generator.getAnswer();
        return null;
    }
    
}
