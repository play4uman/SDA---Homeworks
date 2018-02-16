/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import java.util.LinkedList;
import java.util.List;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;
import RMIServerPackage.SudokuServerInterface;
import GUI.*;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Optional;
import javafx.application.Platform;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Label;

/**
 *
 * @author Play4u
 */
public class SudokuProject extends Application {

    private SudokuServerInterface server;
    
    private LoginScene login = new LoginScene();
    private GameScene game = new GameScene();
    private EndScene end = new EndScene();
    
    private Scene loginScene = new Scene(login.getRoot(), 600, 600);
    private Scene gameScene = new Scene(game.getRoot(), 345, 420);
    private Scene endScene = new Scene(end.getRoot(), 350, 350);
    
    private List<Integer> lockedCells = new LinkedList<>();

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


    private void setNumbers(int[][] solMatrix, TextField[] game) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (Integer.toString(solMatrix[i][j]).equals("0")) {
                    game[i * 9 + j].setText("");
                } else {
                    game[i * 9 + j].setText(Integer.toString(solMatrix[i][j]));
                    game[i * 9 + j].setEditable(false);
                    game[i * 9 + j].setStyle("-fx-font-weight: bold");
                    lockedCells.add(i*9 + j);
                }
            }
        }
    }
    
    private void unlockCells (){
        for (int i = 0; i < lockedCells.size(); i++) {
            game.getMatrix()[lockedCells.get(i)].setEditable(true);
        }
        lockedCells.clear();
        for (int i = 0; i < 81; i++) {
            game.getMatrix()[i].setStyle("-fx-font-weight: normal");
        }
    }


    @Override
    public void start(Stage primaryStage) {
        initializeRMI();
        
        primaryStage.setResizable(true);
        
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
 
        Label lblWrongAns = (Label) game.getRoot().getChildren().get(91);

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
                if (finalAns != null) {
                    lblWrongAns.setVisible(true);
                    
                } else {
                    timer.stop();
                    server.saveStats(username, lblTimer.getText());;
                    end.setTime(lblTimer.getText());
                    end.setEndGameText(true);
                    primaryStage.setScene(endScene);
                    
                }
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        
        Button btnProceed = (Button) game.getRoot().getChildren().get(90);
        btnProceed.setOnAction((eventPrc) -> {;
            end.setTime(lblTimer.getText());
            end.setEndGameText(false);
            primaryStage.setScene(endScene);
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
                  btnCheck.setDisable(true);                     
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
        
        Button btnNewGamePos = (Button) end.getRoot().getChildren().get(3);
        btnNewGamePos.setOnAction((eventNewGamePos) -> {
            primaryStage.setScene(loginScene);
            txtUsername.setText("");
            btnCheck.setDisable(false);
            btnProceed.setVisible(false);
            lblWrongAns.setVisible(false);
            historyList.clear();
            historyIterator = -1;
            unlockCells();
        }); 
       
        Button btnNewGameNeg = (Button) end.getRoot().getChildren().get(4);
        btnNewGameNeg.setOnAction((eventNewGameNeg) -> {
            Alert exitAlert = new Alert(Alert.AlertType.CONFIRMATION);
            exitAlert.setTitle("");
            exitAlert.setHeaderText("Exit game?");
            Optional<ButtonType> resultExit = exitAlert.showAndWait();
            if (resultExit.get() == ButtonType.OK) {
                Platform.exit();
            }
        });

        primaryStage.setTitle("Sudoku");
        primaryStage.show();

    }

    public static void main(String[] args) {
        launch(args);
    }

}
