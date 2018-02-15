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
import java.util.Optional;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.geometry.HPos;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;

/**
 *
 * @author Play4u
 */
public class SudokuProject extends Application {

    private SudokuServerInterface server;
    private GameScene game = new GameScene();
    private LoginScene login = new LoginScene();
    private EndScene end = new EndScene();

    private Difficulty diff;
    private String username;

    MyTimer timer = new MyTimer();

    List<Command> historyList = new LinkedList<>();
    int historyIterator = -1;

    public void initializeRMI() {
        String host = "localhost";
        try {
            //        LocateRegistry.createRegistry(1099);
            Registry registry = LocateRegistry.getRegistry(host, 1099);
            server = (SudokuServerInterface) registry.lookup("Reg");
            System.out.println("Success");
        } catch (Exception ex) {
            ex.printStackTrace();
            System.out.println("Fail");
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

    private void setVerification() {
        TextField[] gameMatrix = game.getMatrix();
        for (int i = 0; i < 81; i++) {
            gameMatrix[i].setOnKeyReleased((event) -> {
                TextField curr = (TextField) event.getSource();
                if (!verifyInput(event) && curr.getText().length() != 0) {
                    if (curr.editableProperty().get() != false) {
                        curr.setText(curr.getText()
                                .substring(0, curr.getText().length() - 1));
                    }
                } else if (event.getCode() == KeyCode.BACK_SPACE
                        || event.getCode() == KeyCode.DELETE) {
                    DeleteCommand delete = new DeleteCommand(curr, curr.getText());
                    delete.execute();
                    for (int j = historyIterator + 1; j < historyList.size(); j++) {
                        historyList.remove(j);
                    }
                    historyList.add(delete);
                    historyIterator++;
                } else if (verifyInput(event)) {
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

    private void setUndoRedoButton() {
        Button btnUndo = (Button) game.getRoot().getChildren().get(86);
        btnUndo.setOnAction((event) -> {
            if (historyIterator >= 0 && !historyList.isEmpty()) {
                historyList.get(historyIterator).undo();
                historyIterator--;
            }
        });

        Button btnRedo = (Button) game.getRoot().getChildren().get(87);
        btnRedo.setOnAction((event) -> {
            if (historyIterator + 1 < historyList.size() && !historyList.isEmpty()) {
                historyIterator++;
                historyList.get(historyIterator).redo();
            }
        });
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

    public void setButtons(GridPane gameGrid, TextField[] grid) {
        Button btnCheck = new Button("Check!");
        btnCheck.setOnAction((event) -> {
        });
        GridPane.setConstraints(btnCheck, 3, 13, 3, 1);

        gameGrid.getChildren().add(btnCheck);
    }

    private void setNumbers(int[][] solMatrix, TextField[] game) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (Integer.toString(solMatrix[i][j]).equals("0")) {
                    game[i * 9 + j].setText("");
                } else {
                    game[i * 9 + j].setText(Integer.toString(solMatrix[i][j]));
                    game[i * 9 + j].setEditable(false);
                    game[i * 9 + j].setStyle("-fx-font-weight: bold");
                }
            }
        }
    }

    private void reset(Label lblTimer) {
        lblTimer.setText("");
    }

    @Override
    public void start(Stage primaryStage) {
        initializeRMI();

        primaryStage.setResizable(true);

        Scene gameScene = new Scene(game.getRoot(), 345, 400);
        Scene loginScene = new Scene(login.getRoot(), 600, 600);

        login.getRoot().setGridLinesVisible(false);
        game.getRoot().setGridLinesVisible(true);
        setVerification();
        setUndoRedoButton();

        primaryStage.setScene(loginScene);

        TextField txtUsername = (TextField) login.getRoot().getChildren().get(2);
        username = txtUsername.getText();

        Label lblTimer = (Label) game.getRoot().getChildren().get(88);
        timer.setLabel(lblTimer);

        Button btnEasy = (Button) login.getRoot().getChildren().get(3);
        Button btnMedium = (Button) login.getRoot().getChildren().get(4);
        Button btnHard = (Button) login.getRoot().getChildren().get(5);
        Label lblInvalidUname = (Label) login.getRoot().getChildren().get(6);

        btnEasy.setOnAction((event) -> {
            username = txtUsername.getText();
            if (!username.equals("")) {
                timer.runTimer();
                diff = Difficulty.EASY;
                primaryStage.setScene(gameScene);
                try {
                    setNumbers(server.generateAndPassSudoku(diff), game.getMatrix());
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            } else {
                lblInvalidUname.setText("Username cannot be empty!");
            }
        });

        btnMedium.setOnAction((event) -> {
            username = txtUsername.getText();
            if (!username.equals("")) {
                timer.runTimer();
                diff = Difficulty.MEDIUM;
                primaryStage.setScene(gameScene);
                try {
                    setNumbers(server.generateAndPassSudoku(diff), game.getMatrix());
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            } else {
                lblInvalidUname.setText("Username cannot be empty!");
            }
        });

        btnHard.setOnAction((event) -> {
            username = txtUsername.getText();
            if (!username.equals("")) {
                timer.runTimer();
                diff = Difficulty.HARD;
                primaryStage.setScene(gameScene);
                try {
                    setNumbers(server.generateAndPassSudoku(diff), game.getMatrix());
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            } else {
                lblInvalidUname.setText("Username cannot be empty!");
            }
        });

        Button btnCheck = (Button) game.getRoot().getChildren().get(85);
        btnCheck.setOnAction((event) -> {
            int[][] answer = new int[9][9];
            TextField[] matrix = game.getMatrix();
            for (int i = 0; i < matrix.length; i++) {
                if (matrix[i].getText().equals("")) {
                    answer[i / 9][i % 9] = 0;
                } else {
                    answer[i / 9][i % 9] = Integer.parseInt(matrix[i].getText());
                }
            }

            try {
                int[][] finalAns = server.checkResult(answer);
                if (finalAns != null) {                                 //Wrong!
                    System.out.println("Wrong answer!");
//                    end = new EndScene(false, lblTimer.getText());
//                    Scene endScene = new Scene(end.getRoot(), 350, 350);
//                    primaryStage.setScene(endScene);
                    
                } else {
                    timer.stop();
                    server.saveStats(username, lblTimer.getText());
                    end.setStatus(true);
                    end.setTime(lblTimer.getText());
                    end.initialize();
                    Scene endScene = new Scene(end.getRoot(), 350, 350);
                    primaryStage.setScene(endScene);
                    Button btnNewGamePos = (Button) end.getRoot().
                            getChildren().get(3);
                    btnNewGamePos.setOnAction((eve) -> {
                        primaryStage.setScene(loginScene);
                        txtUsername.setText("");
                    });
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        
        Button btnProceed = (Button) game.getRoot().getChildren().get(90);
        btnProceed.setOnAction((eventPrc) -> {
            end.setStatus(false);
            end.setTime(lblTimer.getText());
            end.initialize();
            primaryStage.setScene(new Scene(end.getRoot(), 350, 350));
        });
        
        Button btnCheckSol = (Button) game.getRoot().getChildren().get(89);
        btnCheckSol.setOnAction((event)->{
              Alert confirmAlert = new Alert(Alert.AlertType.CONFIRMATION);
              confirmAlert.setTitle("");
              confirmAlert.setHeaderText("View results?");
              String context = String.format("Are you sure you want to view the results?"
                      + "%nDoing so will count as a loss and your score won't be submitted!");
              confirmAlert.setContentText(context);
              Optional<ButtonType> result = confirmAlert.showAndWait();
              if (result.get() == ButtonType.OK){
                  timer.stop();
                  int[][] buffRes = new int[9][9];
                  try{
                      setNumbers(server.checkResult(buffRes), game.getMatrix());
                  }
                  catch(RemoteException ex){
                      ex.printStackTrace();
                  }
                  btnProceed.setVisible(true);
              }
        });

        primaryStage.setTitle("Sudoku");
        primaryStage.show();

    }

    public static void main(String[] args) {
        launch(args);
    }

}
