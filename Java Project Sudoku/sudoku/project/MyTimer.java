/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import javafx.concurrent.Task;
import javafx.scene.control.Label;

/**
 *
 * @author Play4u
 */
public class MyTimer {
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


}
