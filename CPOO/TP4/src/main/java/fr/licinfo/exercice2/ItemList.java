package fr.licinfo.exercice2;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by c16017548 on 04/10/16.
 */
public class ItemList<T> {
    private List<T> items;

    public ItemList() { items = new ArrayList<T>(); }

    public void add(T item) { items.add(item); }

    public void print(ListFormat f){
        System.out.print(f.listStart());
        for (T i : items){
            System.out.print(f.itemStart() + i + f.itemEnd());
        }
        System.out.print(f.listEnd());
    }
}