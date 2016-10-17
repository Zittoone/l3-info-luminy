package fr.licinfo;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 03/10/2016.
 */
public class GridTest {

    @Test
    public void scenarioTest(){
        String[][] elements = { { "A", "C", "E", "G" },
                { "B", "D", "F", "H" } };
        Grid<String> grid = new Grid<String>(elements);

        for (String element : grid){
            System.out.print(element+" ");
        }

        /*for (int line = 0; line < grid.nbLines(); line++)
            for (int column = 0; column < grid.nbColumns(); column++) {
                String element = grid.get(line, column);
                System.out.print(element+" ");
            }
        System.out.println();*/
    }

}