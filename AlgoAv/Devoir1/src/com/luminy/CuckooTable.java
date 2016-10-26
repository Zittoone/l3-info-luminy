package com.luminy;

import javafx.util.Pair;

import java.util.Vector;

/**
 * Created by c16017548 on 21/09/16.
 */
public class CuckooTable<Key extends FamilyHashable, Value> {

    private Vector<Pair<Key, Value>> table1;
    private Vector<Pair<Key, Value>> table2;

    private int nbelement;

    private static final int h1 = 31;
    private static final int h2 = 78;

    private static final int max_iteration = 5;

    public CuckooTable(int expectedKeys) {
        nbelement = 0;

        this.table1 = new Vector<Pair<Key, Value>>(expectedKeys);
        this.table2 = new Vector<Pair<Key, Value>>(expectedKeys);

        table1.setSize(expectedKeys);
        table2.setSize(expectedKeys);
    }

    public boolean isEmpty() {
        return this.nbelement == 0;
    }

    public boolean containsKey(Key key) {

        System.out.println("\n-Containskey : expected -> " + key.toString());
        System.out.println("ref: " + this);
        System.out.println("Table1 1 : " + table1.get(getIndex(key, h1)));
        System.out.println("Table1 2 : " + table2.get(getIndex(key, h2)));
        return (table1.get(getIndex(key, h1)) != null && table1.get(getIndex(key, h1)).getKey().equals(key))
                || (table2.get(getIndex(key, h2)) != null && table2.get(getIndex(key, h2)).getKey().equals(key));
    }

    public Value get(Key key) {

        try {

            if (table1.get(getIndex(key, h1)) != null) {
                Key k1 = table1.get(getIndex(key, h1)).getKey();
                if (key.equals(k1)) {
                    return table1.get(getIndex(k1, h1)).getValue();
                }
            }

            if (table2.get(getIndex(key, h2)) != null) {
                Key k2 = table2.get(getIndex(key, h2)).getKey();
                if (key.equals(k2)) {
                    return table2.get(getIndex(k2, h2)).getValue();
                }
            }
        }
        catch (NullPointerException e){
            e.printStackTrace();
            System.out.println("Argument invalide");
        }

        return null;
    }

    public void put(Key key, Value value) throws Exception {
        int counter = 0;
        nbelement++;
        putT1(key, value, counter);
    }

    private void putT1(Key key, Value value, int counter) throws Exception {
        if (counter > max_iteration)
            throw new Exception("Echec");
        else {
            if (table1.get(getIndex(key, h1)) != null) {
                if(table1.get(getIndex(key, h1)).getKey().equals(key)){
                    table1.set(getIndex(key, h1), new Pair<>(key, value));
                    return;
                }
                Pair<Key, Value> moved_key = table1.get(getIndex(key, h1));
                table1.set(getIndex(key, h1), new Pair<>(key, value));
                counter++;
                putT2(moved_key.getKey(), moved_key.getValue(), counter);
            } else {
                table1.set(getIndex(key, h1), new Pair<>(key, value));
            }
        }
    }

    private void putT2(Key key, Value value, int counter) throws Exception {

        if (table2.get(getIndex(key, h2)) != null) {
            Pair<Key, Value> moved_key = table2.get(getIndex(key, h2));
            table2.set(getIndex(key, h2), new Pair<>(key, value));
            counter++;
            putT1(moved_key.getKey(), moved_key.getValue(), counter);
        }
        else {
            table2.set(getIndex(key, h2), new Pair<>(key, value));
        }
    }

    public void remove(Key key) {
        if (table1.contains(key)){
            table1.remove(key);
            nbelement--;
        }


        else if (table2.contains(key)){
            table2.remove(key);
            nbelement--;
        }
    }

    private int getIndex(Key key, int seed) {
        return Math.abs((int) key.hashCode(seed) % table1.size());
    }

    /*public PrefixTree<Value> get(Character c) {
        return null;
    }*/

}
