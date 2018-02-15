/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import java.util.Timer;
import java.util.TimerTask;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.concurrent.Task;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

/**
 *
 * @author Play4u
 */
public class MyTimer extends Application {
   Label lblToModify;
   boolean status;
    
   public MyTimer(Label lblToModify){
       this.lblToModify = lblToModify;
   }
   
   public MyTimer (){
       this(null);
   }
   
   public void runTimer(){
       status = true;
       Task<Void> task = new Task() {
            int hours, mins, secs;
            String strHrs, strMins, strSecs, result;
            int counter = 0;
            @Override
            public Void call() throws Exception {
                while (status) {
                    counter++;
                    hours = counter / 3600;
                    mins = (counter % 3600) / 60;
                    secs = (counter % 3600) % 60;
                    strHrs = hours <= 9 ? String.format("0%d:", hours) : String.format("%d:", hours);
                    strMins = mins <= 9 ? String.format("0%d:", mins) : String.format("%d:", mins);
                    strSecs = secs <= 9 ? String.format("0%d", secs) : String.format("%d", secs);
                    updateMessage(strHrs + strMins + strSecs);
                    Thread.sleep(1000);
                }
                return null;
            }
        };
        Thread thr = new Thread(task);
        thr.setDaemon(true);
        thr.start();
        lblToModify.textProperty().bind(task.messageProperty());
   }
   
   public void stop (){
       status = false;
   }
   
   public void setLabel (Label lblTarget){
       lblToModify = lblTarget;
   }
    

    @Override
    public void start(Stage primaryStage) throws Exception {
        lblToModify = new Label("");
        GridPane root = new GridPane();
        Scene scene = new Scene(root, 350, 350);
        
        
        
        Button btnStop = new Button("Stop");
        btnStop.setOnAction((event)->{
            stop();
        });
        
        Button btnStart = new Button("Start");
        btnStart.setOnAction((event)->{
            runTimer();
        });
        
        GridPane.setConstraints(btnStart, 0, 0);
        GridPane.setConstraints(btnStop, 1, 0);
        GridPane.setConstraints(lblToModify, 0, 1);
       
        
        root.getChildren().addAll(lblToModify, btnStop, btnStart);
        

        
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    
    public static void main(String[] args) {
        launch(args);
    }

}
