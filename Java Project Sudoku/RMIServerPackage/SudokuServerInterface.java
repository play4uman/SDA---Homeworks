/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RMIServerPackage;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author Play4u
 */
public interface SudokuServerInterface extends Remote {
    public int[][] generateAndPassSudoku()throws RemoteException;
    public int[][] showResult(boolean correctlyAnswered)throws RemoteException;
}
