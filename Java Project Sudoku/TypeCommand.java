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
public class TypeCommand implements Command{
    
    private TextField target;
    private String typed;
    
    public String getTyped(){
        return typed;
    }

    public TypeCommand(TextField target, String typed) {
        this.target = target;
        this.typed = typed;
    }
    
    @Override
    public void execute() {
        target.setText(typed);
    }

    @Override
    public void undo() {
        target.setText("");
    }

    @Override
    public void redo() {
        target.setText(typed);
    }
    
}
