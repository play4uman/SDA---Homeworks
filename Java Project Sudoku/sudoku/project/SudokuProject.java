/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import java.util.LinkedList;
import java.util.List;
import java.util.Stack;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.shape.Line;
import javafx.stage.Stage;
import RMIServerPackage.SudokuServerInterface;
import javafx.scene.layout.VBox;
import GUI.*;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Play4u
 */
public class SudokuProject extends Application {
    private SudokuServerInterface server;
    private GameScene temp = new GameScene();
    
    SolIter solution = new SolIter();
    FXTimer timer = new FXTimer();
    List<Command> historyList = new LinkedList<>();
    int historyIterator = -1;
    
    public void initializeRMI (){
        String host = "localhost";
        try{
    //        LocateRegistry.createRegistry(1099);
            Registry registry = LocateRegistry.getRegistry(host, 1099);
            server = (SudokuServerInterface) registry.lookup("ServerImplementation");
            System.out.println("Success? ");
        }
        catch (Exception ex){
            System.out.println(ex);
            System.out.println("KOR!");
        }
    }

    public void addTextBoxes(GridPane root, TextField[] matrix) {
        int counter = 0;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (i != 3 && i != 7 && j != 3 && j != 7) {
                    GridPane.setConstraints(matrix[counter], j, i);

                    //    GridPane.setFillWidth(matrix[counter], true);
                    GridPane.setFillHeight(matrix[counter], true);
                    root.getChildren().add(matrix[counter]);
                    counter++;
                }
            }
        }
    }
    
    private boolean verifyInput(KeyEvent event) {
        if (event.getCode() != KeyCode.DIGIT1 && event.getCode() != KeyCode.NUMPAD1
                && event.getCode() != KeyCode.DIGIT2 && event.getCode() != KeyCode.NUMPAD2
                && event.getCode() != KeyCode.DIGIT3 && event.getCode() != KeyCode.NUMPAD3
                && event.getCode() != KeyCode.DIGIT4 && event.getCode() != KeyCode.NUMPAD4
                && event.getCode() != KeyCode.DIGIT5 && event.getCode() != KeyCode.NUMPAD5
                && event.getCode() != KeyCode.DIGIT6 && event.getCode() != KeyCode.NUMPAD6
                && event.getCode() != KeyCode.DIGIT7 && event.getCode() != KeyCode.NUMPAD7
                && event.getCode() != KeyCode.DIGIT8 && event.getCode() != KeyCode.NUMPAD8
                && event.getCode() != KeyCode.DIGIT9 && event.getCode() != KeyCode.NUMPAD9) {
            return false;
        }
        return true;
    }

    
    private void setVerification(TextField[] gameMatrix) {
        for (int i = 0; i < 81; i++) {
            gameMatrix[i].setOnKeyReleased((event) -> {
                TextField curr = (TextField) event.getSource();
                if (!verifyInput(event) && curr.getText().length() != 0) {
                    if (curr.editableProperty().get() != false){
                        curr.setText(curr.getText()
                            .substring(0, curr.getText().length() - 1));
                    }
                }
                else if(event.getCode() == KeyCode.BACK_SPACE 
                        || event.getCode() == KeyCode.DELETE){
                    DeleteCommand delete = new DeleteCommand (curr, curr.getText());
                    delete.execute();
                    for (int j = historyIterator + 1; j < historyList.size(); j++) {
                        historyList.remove(j);
                    }
                    historyList.add(delete);
                    historyIterator++;
                }
                else if (verifyInput(event)){
                     TypeCommand typed = new TypeCommand(curr, curr.getText());
                     typed.execute();
                    for (int j = historyIterator + 1; j < historyList.size(); j++) {
                        historyList.remove(j);
                    }
                     historyList.add(typed);
                     historyIterator++;
                }
            });
            
        }
    }
    
    
    private void setUndoRedoButton (GridPane gameGrid){
        Button btnUndo = new Button ("Undo");
        btnUndo.setOnAction((event) -> {
            if (historyIterator >= 0 && !historyList.isEmpty()){
                historyList.get(historyIterator).undo();
                historyIterator--;
            }
        });

        Button btnRedo = new Button("Redo");
        btnRedo.setOnAction((event) -> {
            if (historyIterator + 1 < historyList.size() && !historyList.isEmpty()) {
                historyIterator++;
                historyList.get(historyIterator).redo();
            }
        });
        
        GridPane.setConstraints(btnRedo, 11, 5, 2, 2);
        GridPane.setConstraints(btnUndo, 11, 2, 2, 2);
        gameGrid.getChildren().addAll(btnUndo, btnRedo);
    }
    
    
    
    public void setBorders(GridPane root) {
        int[] verticalIndex = {3, 7};
        int[] horizontIndex = {3, 7};
        for (int i = 0; i < verticalIndex.length; i++) {
            Line border = new Line();
            GridPane.setConstraints(border, verticalIndex[i], 0, 1, 11);
            border.setStartX(12.5);
            border.setStartY(0);
            border.setEndX(12.5);
            border.setEndY(270);
            border.setStrokeWidth(4);
            root.getChildren().add(border);
        }
        for (int j = 0; j < horizontIndex.length; j++) {
            Line border = new Line();
            GridPane.setConstraints(border, 0, horizontIndex[j], 11, 1);
            border.setStartX(0);
            border.setStartY(12.5);
            border.setEndX(325);
            border.setEndY(12.5);
            border.setStrokeWidth(4);
            root.getChildren().add(border);
        }

    }

    public void setPlayingField(GridPane root) {
        final int rowsConst = 13;
        final int colConst = 13;
        for (int i = 0; i < rowsConst; i++) {
            if (i == 3 || i == 7) {
                ColumnConstraints cConst = new ColumnConstraints(5);
                root.getColumnConstraints().add(cConst);
            } else {
                ColumnConstraints cConst = new ColumnConstraints(35);
                root.getColumnConstraints().add(cConst);
            }
        }
        for (int i = 0; i < rowsConst; i++) {
            if (i == 3 || i == 7) {
                RowConstraints rConst = new RowConstraints(5);
                root.getRowConstraints().add(rConst);
            } else {
                RowConstraints rConst = new RowConstraints(30);
                root.getRowConstraints().add(rConst);
            }

        }

    }
    
    public void initialize(TextField[] grid, Difficulty diff){
        solution.setMatrix(grid, diff);
    }
    
    public boolean checkAnswer (TextField[] grid){
        int[][] ans = solution.getAnswer();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if ("".equals(grid[i*9 + j].getText()) || ans[i][j] != Integer.parseInt(grid[i*9 + j].getText()))
                    return false;
            }
        }
        return true;
    }
    
    
    public void setButtons(GridPane gameGrid, TextField[] grid){
        Button btnCheck = new Button("Check!");
        btnCheck.setOnAction((event) -> {
            if (checkAnswer(grid)) {
                System.out.println("CORRECT!");
            } else {
                System.out.println("INCORRECT!");
            }
        });
        GridPane.setConstraints(btnCheck, 3, 13, 3, 1);
        
        gameGrid.getChildren().add(btnCheck);
    }
    
    private void setNumbers(int[][] grid){
        TextField[] curr = temp.getSceneMatrix();
        for (int i = 0; i < 81; i++) {
            curr[i].setText(Integer.toString(grid[i / 9][i % 9]));
        }
    }
    

    @Override
    public void start(Stage primaryStage) {
        initializeRMI();
        
        
        VBox rootLogin = new VBox();
        Scene loginScene = new Scene(rootLogin, 300, 300);
        primaryStage.setScene(loginScene);
        
        primaryStage.setResizable(false);
        
        
        Scene gameScene = new Scene(temp.getSceneRoot(), 400, 400);
        
//        final TextField[] gameMatrix = new TextField[81];
//        for (int i = 0; i < 81; i++) {
//            gameMatrix[i] = new TextField();
//        }
    
        Button btnProceed = new Button ("Proceed");
        btnProceed.setOnAction((e)-> {
            primaryStage.setScene(gameScene);
            try {
                setNumbers(server.generateAndPassSudoku());
            } catch (RemoteException ex) {
                System.out.println(ex);
            }
        });
        rootLogin.getChildren().add(btnProceed);
       
        
//        gameGrid.setGridLinesVisible(false);
//        setPlayingField(gameGrid); // curr
//        addTextBoxes(gameGrid, gameMatrix); //curr
//        setBorders(gameGrid); //curr
//        solution.setMatrix(gameMatrix, Difficulty.EASY); //NOT!
//        setButtons(gameGrid, gameMatrix);
//        setVerification(gameMatrix);//NOT!
//        setUndoRedoButton(gameGrid);
        
        
        primaryStage.setTitle("Sudoku");
        primaryStage.show();

    }

    public static void main(String[] args) {
        launch(args);
    }

}
