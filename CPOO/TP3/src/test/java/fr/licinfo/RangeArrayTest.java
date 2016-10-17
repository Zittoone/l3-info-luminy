package fr.licinfo;

import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 03/10/2016.
 */
public class RangeArrayTest {

    @Test
    public void scenarioTest(){
        int indexMin = -3;
        int indexMax = 1;
        RangeArray squares = new RangeArray(indexMin, indexMax);
        for (int index =  squares.getIndexMin();
             index <= squares.getIndexMax();
             index++)
            squares.set(index, index*index);
        for (int index =  squares.getIndexMin();
             index <= squares.getIndexMax();
             index++)
            System.out.println(index + " -> " + squares.get(index));
        System.out.println(squares.rangeSize());
    }

    @Test
    public void scenarioTestGenerique(){
        RangeArray<String> habitations = new RangeArray<String>(3, 5);
        habitations.set(3, "Maison");
        habitations.set(4, "Immeuble");
        habitations.set(5, "Hutte");
        for (int index =  habitations.getIndexMin();
             index <= habitations.getIndexMax();
             index++)
            System.out.print(habitations.get(index).length() + " ");
    }

    @Test
    public void scenarioTestInterable(){
        RangeArray<String> habitations = new RangeArray<String>(3, 5);
        habitations.set(3, "Maison");
        habitations.set(4, "Immeuble");
        habitations.set(5, "Hutte");
        for (String habitation : habitations)
            System.out.print(habitation + " ");
    }

    @Test
    public void getIndexMin() throws Exception {

    }

    @Test
    public void getIndexMax() throws Exception {

    }

    @Test
    public void get() throws Exception {

    }

    @Test
    public void rangeSize() throws Exception {

    }

    @Test
    public void set() throws Exception {

    }

}