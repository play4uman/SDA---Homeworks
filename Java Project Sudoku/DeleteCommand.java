/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

import javafx.scene.control.TextField;

/**
 *
 * @author Play4u
 */
public class DeleteCommand implements Command{
    private TextField target;
    String toDel;

    public DeleteCommand(TextField target, String toDel) {
        this.target = target;
        this.toDel = toDel;
    }
    
    @Override
    public void execute() {
        target.setText("");
    }

    @Override
    public void undo() {
        target.setText(toDel);
    }

    @Override
    public void redo() {
        target.setText("");
    }
    
}
