/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

/**
 *
 * @author Play4u
 */
public class LoginScene extends Application{

    @Override
    public void start(Stage primaryStage) throws Exception {
        GridPane root = new GridPane();
        Scene currScene = new Scene(root, 300, 300);
        
        Label lblUsername = new Label("Username: ");
        TextField txtUsername = new TextField();
        
        root.getChildren().addAll(lblUsername, txtUsername);
        
        primaryStage.setScene(currScene);
        primaryStage.show();
    }
    
    public static void main(String[] args) {
        launch(args);
    }
    
}
