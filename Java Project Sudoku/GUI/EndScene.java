/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import javafx.geometry.HPos;
import javafx.geometry.VPos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.RowConstraints;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

/**
 *
 * @author Play4u
 */


public class EndScene {
    
    
    GridPane root;
    private String time;
    private Label lblEnd;
    private Label lblYourTime;

    public EndScene(String time) {
        this.time = time;
        root = new GridPane();
        initialize();
    }
    
    public EndScene (){
        this(null);
        root = new GridPane();
        initialize();
    }
    
    public void setTime(String time){
        this.time = time;
    }
    


    public void initialize() {
        for (int i = 0; i < 10; i++) {
            RowConstraints rCon;
            rCon = new RowConstraints(35);
            root.getRowConstraints().add(rCon);
        }

        for (int i = 0; i < 10; i++) {
            ColumnConstraints cCon;
            cCon = new ColumnConstraints(35);
            root.getColumnConstraints().add(cCon);
        }

        lblEnd = new Label();
        lblEnd.setFont(new Font("Arial", 32));
        GridPane.setHalignment(lblEnd, HPos.CENTER);
        GridPane.setValignment(lblEnd, VPos.CENTER);
        GridPane.setConstraints(lblEnd, 0, 0, 10, 4);
        
        
        lblYourTime = new Label();
        lblYourTime.setFont(new Font("Arial", 18));
        GridPane.setConstraints(lblYourTime, 0, 4, 10, 1);
        GridPane.setHalignment(lblYourTime, HPos.CENTER);
        
        
        Label lblNewGame = new Label("Start a new game?");
        lblNewGame.setFont(new Font("Arial", 24));
        GridPane.setConstraints(lblNewGame, 0, 5, 10 ,1);
        GridPane.setHalignment(lblNewGame, HPos.CENTER);

        Button btnNewGamePos = new Button("Yes");
        GridPane.setConstraints(btnNewGamePos, 1, 7, 3, 2);
        btnNewGamePos.setMinSize(105, 70);
        
        Button btnNewGameNeg = new Button("No");
        btnNewGameNeg.setMinSize(105, 70);
        GridPane.setConstraints(btnNewGameNeg, 6, 7, 3, 2);
        
        root.getChildren().addAll(lblEnd, lblYourTime, lblNewGame, btnNewGamePos ,btnNewGameNeg);
    }
    
    
    public void setEndGameText(boolean status){
        if (status) {
            String strWin = String.format("Congratulations!%n\tYou win!");
            lblEnd.setText(strWin);
            lblEnd.setTextFill(Color.web("#ff0000"));
            lblYourTime.setText("Your time: " + time);
        } else {
            lblEnd.setText("You lose :(");
            lblEnd.setTextFill(Color.web("#0000ff"));
        }
    }


    public GridPane getRoot() {
        return root;
    }
}
