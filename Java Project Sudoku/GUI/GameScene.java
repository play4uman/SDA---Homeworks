/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import javafx.geometry.Insets;
import javafx.scene.control.Button;
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
    }

    public void setPlayingField() {
        final int rowsConst = 13;
        final int colConst = 13;
        for (int i = 0; i < rowsConst; i++) {
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
        GridPane.setConstraints(btnCheck, 3, 13, 3, 1);
        
        Button btnUndo = new Button ("Undo");
        GridPane.setConstraints(btnUndo, 11, 2, 2, 2);
        
        Button btnRedo = new Button ("Redo");
        GridPane.setConstraints(btnRedo, 11, 5, 2, 2);
        
        gameGrid.getChildren().addAll(btnCheck, btnUndo, btnRedo);
        
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
    
    public GridPane getSceneRoot(){
        initialize();
        return gameGrid;
    }
    
    public TextField[] getSceneMatrix(){
        return matrix;
    }
}
