/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RMIServerPackage;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import sudoku.project.Difficulty;

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
    public int[][] generateAndPassSudoku(Difficulty diff) throws RemoteException{
          return generator.getUncompletedMatrix(diff);
    }

    @Override
    public int[][] checkResult(int[][] givenAnswer) throws RemoteException{
             if (generator.checkAnswer(givenAnswer))
                 return null;
             else{
                return generator.getAnswer();
             }    
    }

    @Override
    public void saveStats(String username, String time) throws RemoteException, IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter("stats.txt", true));
        String toWrite = String.format("%s %s %n", username, time);
        writer.write(toWrite);
        writer.close();
    }
    
    
}
