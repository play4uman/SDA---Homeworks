/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sudoku.project;

/**
 *
 * @author Play4u
 */
public interface Command {
    void execute();
    void undo();
    void redo();
}
