/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import javafx.application.Application;
import javafx.beans.property.DoubleProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.HPos;
import javafx.geometry.VPos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import sudoku.project.Difficulty;

/**
 *
 * @author Play4u
 */
public class LoginScene {
    
    private GridPane root;
    
    public LoginScene () {
        initialize();
    }
    
    private void initialize () {
        root = new GridPane();
        
        for (int i = 0; i < 2; i++){
            ColumnConstraints cCon = new ColumnConstraints(300);
            root.getColumnConstraints().add(cCon);
        }
        
        for (int i = 0; i < 7; i++){
            RowConstraints rCon;
            if (i == 1 || i == 2){
                rCon = new RowConstraints(50);
            }
            else if (i == 6){
                rCon = new RowConstraints(50);
            }
            else{
                rCon = new RowConstraints(100);
            }
            root.getRowConstraints().add(rCon);
        }
        
        root.setGridLinesVisible(false);
        Label lblUsername = new Label("Username: ");
        lblUsername.setFont(new Font("Arial", 30));
        GridPane.setConstraints(lblUsername, 0, 0, 1, 1,HPos.CENTER, VPos.BOTTOM);
        
        Label lblDiff = new Label("Please select difficulty:");
        lblDiff.setFont(new Font("Arial", 24));
        GridPane.setConstraints(lblDiff, 0, 2, 2, 1, HPos.CENTER, VPos.CENTER);
        
        TextField txtUsername = new TextField();
        txtUsername.setMaxWidth(200);
        GridPane.setConstraints(txtUsername, 1, 0, 1, 1, HPos.LEFT, VPos.BOTTOM);
        
        Button btnEasy = new Button("EASY");
        btnEasy.setMinSize(300, 50);
        GridPane.setConstraints(btnEasy, 0, 3, 2 , 1, HPos.CENTER, VPos.CENTER);
        
        Button btnMedium = new Button("MEDIUM");
        btnMedium.setMinSize(300, 50);
        GridPane.setConstraints(btnMedium, 0, 4, 2 , 1, HPos.CENTER, VPos.CENTER);
        
        Button btnHard = new Button("HARD");
        btnHard.setMinSize(300, 50);
        GridPane.setConstraints(btnHard, 0, 5, 2 , 1, HPos.CENTER, VPos.CENTER);
        
        Label lblInvalidUName = new Label("");
        lblInvalidUName.setFont(new Font ("Arial", 20));
        lblInvalidUName.setTextFill(Color.web("#ff0000"));
        GridPane.setConstraints(lblInvalidUName, 1, 6, 1 ,1 , HPos.RIGHT, VPos.CENTER);
        
        root.getChildren().addAll(lblUsername, lblDiff, txtUsername, btnEasy,
        btnMedium, btnHard, lblInvalidUName);
    }
    
    public GridPane getRoot () {
        return root;
    }
    
}
