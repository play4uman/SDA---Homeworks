/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RMIServerPackage;

import java.io.IOException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import sudoku.project.Difficulty;


/**
 *
 * @author Play4u
 */
public interface SudokuServerInterface extends Remote {
    public int[][] generateAndPassSudoku(Difficulty diff)throws RemoteException;
    public int[][] checkResult(int[][] toBeChecked)throws RemoteException;
    public void saveStats(String username, String time)throws RemoteException, IOException;
}
