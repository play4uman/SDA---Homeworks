/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Stack;

/**
 *
 * @author Play4u
 */
public class SolIter {
    
    private int matrix[][];
    private List<Integer>[] rng;
    private Stack<Integer> visited;
    
    
    private void initialize (){
        matrix = new int[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                matrix[i][j] = -1;
            }
        }
        
//        indexes = new LinkedList<>();
//        for (int i = 0; i < 81; i++) {
//            indexes.add(i);
//        }
//        Collections.shuffle(indexes);
        
        rng = new ArrayList[81];
        for (int i = 0; i < 81; i++) {
            rng[i] = new ArrayList<Integer>();
            for (int j = 1; j < 10; j++) {
                rng[i].add(j);
            }
            Collections.shuffle(rng[i]);
        }
        
        visited = new Stack<>();
    }
    
    private int squareIndex(int i) {
        if ((i >= 0 && i <= 2) || (i >= 9 && i <= 11) || (i >= 18 && i <= 20)) {
            return 0;
        }
        if ((i >= 3 && i <= 5) || (i >= 12 && i <= 14) || (i >= 21 && i <= 23)) {
            return 1;
        }
        if ((i >= 6 && i <= 8) || (i >= 15 && i <= 17) || (i >= 24 && i <= 26)) {
            return 2;
        }
        if ((i >= 27 && i <= 29) || (i >= 36 && i <= 38) || (i >= 45 && i <= 47)) {
            return 3;
        }
        if ((i >= 30 && i <= 32) || (i >= 39 && i <= 41) || (i >= 48 && i <= 50)) {
            return 4;
        }
        if ((i >= 33 && i <= 35) || (i >= 42 && i <= 44) || (i >= 51 && i <= 53)) {
            return 5;
        }
        if ((i >= 54 && i <= 56) || (i >= 63 && i <= 65) || (i >= 72 && i <= 74)) {
            return 6;
        }
        if ((i >= 57 && i <= 59) || (i >= 66 && i <= 68) || (i >= 75 && i <= 77)) {
            return 7;
        }
        if ((i >= 60 && i <= 62) || (i >= 69 && i <= 71) || (i >= 78 && i <= 80)) {
            return 8;
        }
        return 42;
    }
    
    private boolean isInRow (int index, int n){
        int row = index / 9;
        int left = index % 9;
        int right = index % 9;
        while (left >= 0){
            if (matrix[row][left] == n)
                return true;
            left--;
        }
        while (right <= 8){
            if (matrix[row][right] == n)
                return true;
            right++;
        }
        return false;
    }
    
    private boolean isInCol (int index, int n){
        int col = index % 9;
        int up = index / 9;
        int down = index / 9;
        while (up >= 0){
            if (matrix[up][col] == n)
                return true;
            up--;
        }
        while (down <= 8){
            if (matrix[down][col] == n)
                return true;
            down++;
        }
        return false;
    }
    
    private boolean isInSquare (int index, int n){
        int square = squareIndex(index);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (squareIndex(i*9 + j) == square && i*9 + j != index){
                    if (matrix[i][j] == n)
                        return true;    
                }
            }
        }
        
        return false;
    }
    
    private void replenishSet(int index){
        for (int i = 1; i < 10; i++) {
            rng[index].add(i);
        }
        Collections.shuffle(rng[index]);
    }
    
    private boolean placeNumber (int index){
        int n;
        
        for (int i = 0; i < rng[index].size(); i++) {
           
            n = rng[index].get(i);
            if (!isInRow(index, n) && !isInCol(index, n) && !isInSquare(index, n)) {
                matrix[index / 9][index % 9] = n;
                rng[index].remove((Integer) n);
                return true;
            } 
        }
        return false;
    }
    
    public int[][] getSolutionMatrix (){
        initialize();
        int currIndex = 0;
        
        while (currIndex != 81){
    
            visited.push(currIndex);
            if (placeNumber(currIndex)){
                currIndex++;
            }
            else{
                matrix[currIndex / 9][currIndex % 9] = -1;
                replenishSet(currIndex);
                visited.pop();
                currIndex = visited.pop();
            }
        }
        return matrix;
    }
    
    private void tempPrint(){
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.printf(matrix[i][j] + " ");
            }
            System.out.println("");
        }
        System.out.printf("\n\n");
    }
    
    
    private void print (){
        getSolutionMatrix();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                System.out.printf(matrix[i][j] + " ");
            }
            System.out.println("");
        }
    }
    
}
