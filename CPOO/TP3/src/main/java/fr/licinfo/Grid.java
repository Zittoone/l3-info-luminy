package fr.licinfo;

import java.util.Iterator;

/**
 * Created by Alexis Couvreur on 03/10/2016.
 */
public class Grid<T> implements Iterable<T> {
    private T[][] elements;

    public Grid(T[][] elements) {
        this.elements = elements;
    }

    public T get(int line, int column) {
        return elements[line][column];
    }

    public int nbLines() {
        return elements.length;
    }

    public int nbColumns() {
        return elements[0].length;
    }

    public T[][] getElements(){
        return elements;
    }

    public Iterator<T> iterator() {
        return new GridIterator<T>(this);
    }
}