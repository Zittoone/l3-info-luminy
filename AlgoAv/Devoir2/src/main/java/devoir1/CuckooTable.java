package devoir1;

import javafx.util.Pair;

import java.util.*;

/**
 * Created by c16017548 on 21/09/16.
 * Cette classe implémente Itérable, pour l'implémentation Map voir "CuckooMap"
 */
public class CuckooTable<Key extends FamilyHashable, Value> implements Iterable {

    private Vector<Pair<Key, Value>> table1;
    private Vector<Pair<Key, Value>> table2;

    private int size;

    private static final int h1 = 31;
    private static final int h2 = 78;

    private int MAX_ITERATION;

    public CuckooTable(int expectedKeys) {
        size = 0;

        this.table1 = new Vector<Pair<Key, Value>>(expectedKeys);
        this.table2 = new Vector<Pair<Key, Value>>(expectedKeys);

        table1.setSize(expectedKeys);
        table2.setSize(expectedKeys);

        MAX_ITERATION = expectedKeys/2;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public boolean containsKey(Key key) {

        Pair<Key, Value> P1 = table1.get(getIndex(key, h1));
        Pair<Key, Value> P2 = table2.get(getIndex(key, h2));

        return (P1 != null && P1.getKey().equals(key))
                || (P2 != null && P2.getKey().equals(key));
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
        size++;
        putT1(key, value, counter);
    }

    private void putT1(Key key, Value value, int counter) throws Exception {
        if (counter > MAX_ITERATION)
            throw new Exception("Echec");
        else {
            // Déjà occupé
            if (table1.get(getIndex(key, h1)) != null) {
                if(table1.get(getIndex(key, h1)).getKey().equals(key)){
                    table1.set(getIndex(key, h1), new Pair<Key, Value>(key, value));
                    return;
                }
                Pair<Key, Value> moved_key = table1.get(getIndex(key, h1));
                table1.set(getIndex(key, h1), new Pair<Key, Value>(key, value));
                counter++;
                putT2(moved_key.getKey(), moved_key.getValue(), counter);
            }
            // Non occupé
            else {
                table1.set(getIndex(key, h1), new Pair<Key, Value>(key, value));
            }
        }
    }

    private void putT2(Key key, Value value, int counter) throws Exception {

        if (table2.get(getIndex(key, h2)) != null) {
            Pair<Key, Value> moved_key = table2.get(getIndex(key, h2));
            table2.set(getIndex(key, h2), new Pair<Key, Value>(key, value));
            counter++;
            putT1(moved_key.getKey(), moved_key.getValue(), counter);
        }
        else {
            table2.set(getIndex(key, h2), new Pair<Key, Value>(key, value));
        }
    }

    public void remove(Key key) {
        if (table1.get(getIndex(key, h1)) != null) {
            Key k1 = table1.get(getIndex(key, h1)).getKey();
            if (key.equals(k1)) {
                table1.set(getIndex(k1, h1), null);
                size--;
            }
        }

        if (table2.get(getIndex(key, h2)) != null) {
            Key k2 = table2.get(getIndex(key, h2)).getKey();
            if (key.equals(k2)) {
                table2.set(getIndex(k2, h2), null);
                size--;
            }
        }

    }

    public int size(){
        return size;
    }

    public Vector<Pair<Key, Value>> getTable1() {
        return table1;
    }

    public Vector<Pair<Key, Value>> getTable2() {
        return table2;
    }

    private int getIndex(Key key, int seed) {
        return Math.abs((int) key.hashCode(seed) % table1.size());
    }

    public Iterator iterator() {
        return new CuckooTableIterator<Key, Value>(this);
    }
}
