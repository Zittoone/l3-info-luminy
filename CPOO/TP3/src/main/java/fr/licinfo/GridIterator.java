package fr.licinfo;

import java.util.Arrays;
import java.util.Iterator;

/**
 * Created by Alexis Couvreur on 03/10/2016.
 */
public class GridIterator<T> implements Iterator<T> {

    private T[][] elements;
    private int currentTab = 0;
    private int current = 0;

    public GridIterator(Grid<T> ts) {
        this.elements = ts.getElements();
    }

    public boolean hasNext() {
        return !(current == elements[currentTab].length && currentTab == elements.length - 1);
    }

    public T next() {
        if(current == elements[currentTab].length){
            currentTab++;
            current = 0;
        }

        return elements[currentTab][current++];
    }

    @Override
    public void remove() {

    }
}
