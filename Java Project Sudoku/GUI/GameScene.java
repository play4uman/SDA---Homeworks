/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.geometry.VPos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.shape.Line;

/**
 *
 * @author Play4u
 */
public class GameScene {

    private GridPane gameGrid;
    private TextField[] matrix;

    public GameScene() {
        System.out.println("Initialized");
        gameGrid = new GridPane();
        matrix = new TextField[81];
        for (int i = 0; i < 81; i++) {
            matrix[i] = new TextField();
        }
        initialize();
    }

    public void setPlayingField() {
        final int rowsConst = 15;
        final int colConst = 11;
        for (int i = 0; i < colConst; i++) {
            if (i == 3 || i == 7) {
                ColumnConstraints cConst = new ColumnConstraints(5);
                gameGrid.getColumnConstraints().add(cConst);
            } else {
                ColumnConstraints cConst = new ColumnConstraints(35);
                gameGrid.getColumnConstraints().add(cConst);
            }
        }
        for (int i = 0; i < rowsConst; i++) {
            if (i == 3 || i == 7) {
                RowConstraints rConst = new RowConstraints(5);
                gameGrid.getRowConstraints().add(rConst);
            } else {
                RowConstraints rConst = new RowConstraints(30);
                gameGrid.getRowConstraints().add(rConst);
            }

        }

    }
        
    private void setTextBoxes() {
        int counter = 0;
        for (int i = 0; i < 11; i++) {
            for (int j = 0; j < 11; j++) {
                if (i != 3 && i != 7 && j != 3 && j != 7) {
                    GridPane.setConstraints(matrix[counter], j, i);
                    GridPane.setFillHeight(matrix[counter], true);
                    gameGrid.getChildren().add(matrix[counter]);
                    counter++;
                }
            }
        }
    }
    
    private void setBorders() {
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
            gameGrid.getChildren().add(border);
        }
        for (int j = 0; j < horizontIndex.length; j++) {
            Line border = new Line();
            GridPane.setConstraints(border, 0, horizontIndex[j], 11, 1);
            border.setStartX(0);
            border.setStartY(12.5);
            border.setEndX(325);
            border.setEndY(12.5);
            border.setStrokeWidth(4);
            gameGrid.getChildren().add(border);
        }
    }
    
    
    private void setButtons() {
        Button btnCheck = new Button("Check!");
        GridPane.setConstraints(btnCheck, 4, 12, 3, 1);
        btnCheck.setMinSize(105, 15);
        
        Button btnUndo = new Button ("Undo");
        GridPane.setConstraints(btnUndo, 1, 12, 2, 1);
        
        Button btnRedo = new Button ("Redo");
        GridPane.setConstraints(btnRedo, 9, 12, 2, 1);
        
        gameGrid.getChildren().addAll(btnCheck, btnUndo, btnRedo);
        
        Label lblTimer = new Label();
        GridPane.setConstraints(lblTimer, 5, 11, 3, 1);
        gameGrid.getChildren().add(lblTimer);
        
        String strBtnCheckSol = String.format("Check%nsolution");
        Button btnCheckSolution = new Button (strBtnCheckSol);
        GridPane.setConstraints(btnCheckSolution, 4, 13, 3, 2);
        GridPane.setHalignment(btnCheckSolution, HPos.CENTER);
        GridPane.setValignment(btnCheckSolution, VPos.BOTTOM);
        
        gameGrid.getChildren().add(btnCheckSolution);
        
        Button btnProceed = new Button("Proceed");
        GridPane.setConstraints(btnProceed, 8, 14, 3, 1);
        GridPane.setHalignment(btnProceed, HPos.CENTER);
        btnProceed.setVisible(false);
        gameGrid.getChildren().add(btnProceed);
        
       /*
            btnUndo.setOnAction((event) -> {
            if (historyIterator >= 0 && !historyList.isEmpty()){
                historyList.get(historyIterator).undo();
                historyIterator--;
            }
        });
            btnRedo.setOnAction((event)->{
            if(historyIterator + 1 < historyList.size() && !historyList.isEmpty()){
                historyIterator++;
                historyList.get(historyIterator).redo();
            }
        }); 
        */
    }
    

    private void initialize() {
        gameGrid.setPadding(new Insets(10, 10, 10, 10));
        setPlayingField();
        setTextBoxes();
        setBorders();
        setButtons();
    }
    
    public GridPane getRoot(){
        return gameGrid;
    }
    
    public TextField[] getMatrix(){
        return matrix;
    }
}
