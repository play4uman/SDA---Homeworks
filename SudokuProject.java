/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.event.EventType;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.Background;
import javafx.scene.layout.BackgroundFill;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.CornerRadii;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Line;
import javafx.stage.Stage;

/**
 *
 * @author Play4u
 */
public class SudokuProject extends Application {

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
        final int rowsConst = 11;
        final int colConst = 11;
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
    
    public void initialize(TextField[] grid){
        SolIter temp = new SolIter();
        int[][] matrix = temp.getSolutionMatrix();
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                grid[i*9 + j].setText(Integer.toString(matrix[i][j]));
            }
        }
        
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setResizable(true);
        GridPane gameGrid = new GridPane();
        Scene scene = new Scene(gameGrid, 400, 400);
        gameGrid.setPadding(new Insets(10, 10, 10, 10));

        TextField[] gameMatrix = new TextField[81];
        for (int i = 0; i < 81; i++) {
            gameMatrix[i] = new TextField();
        }
        

        //gameGrid.setGridLinesVisible(true);
        setPlayingField(gameGrid);
        addTextBoxes(gameGrid, gameMatrix);
        setBorders(gameGrid);
        Button btn = new Button("Generate");
        btn.setOnAction((event) -> {initialize(gameMatrix);});
        GridPane.setConstraints(btn, 3, 13, 3, 1);
        gameGrid.getChildren().add(btn);
        initialize(gameMatrix);

        primaryStage.setTitle("Sudoku");
        primaryStage.setScene(scene);
        primaryStage.show();

    }

    public static void main(String[] args) {
        launch(args);
    }

}
