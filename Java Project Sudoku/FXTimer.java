/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.beans.property.DoubleProperty;
import javafx.beans.property.SimpleDoubleProperty;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Label;
import javafx.util.Duration;

public class FXTimer {

    private Timeline timeline;
    private DoubleProperty timeSeconds = new SimpleDoubleProperty();
    private Duration time = Duration.ZERO;

    public void execute(Label timerLabel) {
        timerLabel.textProperty().bind(timeSeconds.asString());
        timeline = new Timeline(
                new KeyFrame(Duration.millis(100), (ActionEvent t) -> {
                    Duration duration = ((KeyFrame) t.getSource()).getTime();
                    time = time.add(duration);
                    timeSeconds.set(time.toSeconds());
        })
        );
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
    }
}
