/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package RMIServerPackage;

import java.io.Serializable;
import sudoku.project.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import javafx.scene.control.TextField;

/**
 *
 * @author Play4u
 */
public class SolIter implements Serializable {

    private int matrix[][];
    private int answer[][];
    private List<Integer>[] rng;
    private Stack<Integer> visited;

    public SolIter() {
    }

    private void initialize() {
        matrix = new int[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                matrix[i][j] = -1;
            }
        }

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

    private boolean isInRow(int index, int n) {
        int row = index / 9;
        int left = index % 9;
        int right = index % 9;
        while (left >= 0) {
            if (matrix[row][left] == n) {
                return true;
            }
            left--;
        }
        while (right <= 8) {
            if (matrix[row][right] == n) {
                return true;
            }
            right++;
        }
        return false;
    }

    private boolean isInCol(int index, int n) {
        int col = index % 9;
        int up = index / 9;
        int down = index / 9;
        while (up >= 0) {
            if (matrix[up][col] == n) {
                return true;
            }
            up--;
        }
        while (down <= 8) {
            if (matrix[down][col] == n) {
                return true;
            }
            down++;
        }
        return false;
    }

    private boolean isInSquare(int index, int n) {
        int square = squareIndex(index);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (squareIndex(i * 9 + j) == square && i * 9 + j != index) {
                    if (matrix[i][j] == n) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    private void replenishSet(int index) {
        for (int i = 1; i < 10; i++) {
            rng[index].add(i);
        }
        Collections.shuffle(rng[index]);
    }

    private boolean placeNumber(int index) {
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

    private void getFullMatrix() {
        initialize();
        int currIndex = 0;

        while (currIndex != 81) {

            visited.push(currIndex);
            if (placeNumber(currIndex)) {
                currIndex++;
            } else {
                matrix[currIndex / 9][currIndex % 9] = -1;
                replenishSet(currIndex);
                visited.pop();
                currIndex = visited.pop();
            }
        }
    }


    private boolean isCompleted(int[][] toCheck) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (toCheck[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    private void setDiff(Difficulty diff) {
        getFullMatrix();
        List<Integer> holes = new ArrayList<>();
        for (int i = 0; i < 81; i++) {
            holes.add(i);
        }
        Collections.shuffle(holes);

        switch (diff) {
            case EASY: {
                for (int i = 0; i < 40; i++) {
                    matrix[holes.get(i) / 9][holes.get(i) % 9] = 0;
                }
            }
            break;
            case MEDIUM: {
                for (int i = 0; i < 47; i++) {
                    matrix[holes.get(i) / 9][holes.get(i) % 9] = 0;
                }
            }
            break;
            case HARD: {
                for (int i = 0; i < 52; i++) {
                    matrix[holes.get(i) / 9][holes.get(i) % 9] = 0;
                }
            }
            break;
        }

    }

//    private List<Integer> getPossibilities(int index) {
//        List<Integer> possible = new LinkedList<>();
//        for (int i = 1; i < 10; i++) {
//            if (!isInRow(index, i) && !isInCol(index, i) && !isInSquare(index, i)) {
//                possible.add(i);
//            }
//        }
//        return possible;
//    }

//    private boolean placeANumberUniqueness(int index, int[][] candidate) {
//        int n;
//        for (int i = 0; i < rng[index].size(); i++) {
//            n = rng[index].get(i);
//            if (!isInRow(index, n) && !isInCol(index, n) && !isInSquare(index, n)) {
//                candidate[index / 9][index % 9] = n;
//                rng[index].remove((Integer) n);
//                return true;
//            }
//        }
//        return false;
//    }

//    private boolean matchesAnswer(int[][] candidate) {
//        for (int i = 0; i < 9; i++) {
//            for (int j = 0; j < 9; j++) {
//                if (candidate[i][j] != matrix[i][j]) {
//                    return false;
//                }
//            }
//        }
//        return true;
//    }

//    private void printStack() {
//        Stack<Integer> temp = (Stack<Integer>) visited.clone();
//        while (!temp.isEmpty()) {
//            System.out.printf(temp.pop() + " ");
//        }
//        System.out.println("");
//    }

    public int[][] getUncompletedMatrix(Difficulty diff) {
        setDiff(diff);
        answer = new int[9][9];
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                answer[i][j] = matrix[i][j];
            }
        }
        return matrix;
    }
    
    private boolean checkRowAns(int[][] toBeChecked, int index, int n) {
        int row = index / 9;
        int left = index % 9;
        int right = index % 9;
        while (left >= 0) {
            if (toBeChecked[row][left] == n) {
                return true;
            }
            left--;
        }
        while (right <= 8) {
            if (toBeChecked[row][right] == n) {
                return true;
            }
            right++;
        }
        return false;
    }

    private boolean checkColAns(int[][] toBeChecked,int index, int n) {
        int col = index % 9;
        int up = index / 9;
        int down = index / 9;
        while (up >= 0) {
            if (toBeChecked[up][col] == n) {
                return true;
            }
            up--;
        }
        while (down <= 8) {
            if (toBeChecked[down][col] == n) {
                return true;
            }
            down++;
        }
        return false;
    }

    private boolean checkSquareAns(int[][] toBeChecked, int index, int n) {
        int square = squareIndex(index);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (squareIndex(i * 9 + j) == square && i * 9 + j != index) {
                    if (toBeChecked[i][j] == n) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    private boolean checkNumber(int[][] toBeChecked, int index, int n) {
        return !checkColAns(toBeChecked, index, n) || !checkRowAns(toBeChecked, index, n) || !checkSquareAns(toBeChecked, index, n);
    }

    public boolean checkAnswer(int[][] toBeChecked) {
        for (int i = 0; i < 81; i++) {
            if (!checkNumber(toBeChecked, i, toBeChecked[i / 9][i % 9])) {
                return false;
            }
        }
        return true;
    }
    
    public int[][] getAnswer (){
        return answer;
    }
}

