package com.luminy;

import javafx.util.Pair;

import java.util.Vector;

/**
 * Created by c16017548 on 21/09/16.
 */
public class CuckooTable<Key extends FamilyHashable, Value> {

    private Vector<Pair<Key, Value>> table1;
    private Vector<Pair<Key, Value>> table2;

    private static final int h1 = 31;
    private static final int h2 = 78;

    private static final int max_iteration = 5;

    public CuckooTable(int expectedKeys) {
        this.table1 = new Vector<Pair<Key, Value>>(expectedKeys);
        this.table2 = new Vector<Pair<Key, Value>>(expectedKeys);

        for (int i = 0; i < expectedKeys; i++) {
            table1.add(i, null);
            table2.add(i, null);
        }
    }

    public boolean isEmpty() {
        return table1.isEmpty() && table2.isEmpty();
    }

    public boolean containsKey(Key key) {
        return table1.contains(key) || table2.contains(key);
    }

    public Value get(Key key) {

        try {

            if (table1.get(getIndex(key, h1)) != null) {
                Key k1 = table1.get(getIndex(key, h1)).getKey();
                if (key == k1) {
                    return table1.get(getIndex(k1, h1)).getValue();
                }
            }

            if (table2.get(getIndex(key, h2)) != null) {
                Key k2 = table2.get(getIndex(key, h2)).getKey();
                if (key == k2) {
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
        putT1(key, value, counter);
    }

    private void putT1(Key key, Value value, int counter) throws Exception {
        if (counter > max_iteration)
            throw new Exception("Echec");
        else {
            if (table1.get(getIndex(key, h1)) != null) {
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
        if (table1.contains(key))
            table1.remove(key);

        else if (table2.contains(key))
            table2.remove(key);
    }

    private int getIndex(Key key, int seed) {
        return Math.abs((int) key.hashCode(seed) % table1.size());
    }

    public PrefixTree<Value> get(Character c) {
        return null;
    }

}
