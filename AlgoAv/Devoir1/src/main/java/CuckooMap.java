import javafx.util.Pair;

import java.security.Key;
import java.util.Collection;
import java.util.Map;
import java.util.Set;
import java.util.Vector;

/**
 * Created by sebastientosello on 30/10/2016.
 */
public class CuckooMap<Key extends FamilyHashable, Value> implements Map<Key, Value> {
    private Vector<Pair<Key, Value>> table1;
    private Vector<Pair<Key, Value>> table2;

    private int size;

    private static final int h1 = 31;
    private static final int h2 = 78;

    private int MAX_ITERATION;

    public CuckooMap(int expectedKeys) {
        size = 0;

        this.table1 = new Vector<Pair<Key, Value>>(expectedKeys);
        this.table2 = new Vector<Pair<Key, Value>>(expectedKeys);

        table1.setSize(expectedKeys);
        table2.setSize(expectedKeys);

        MAX_ITERATION = expectedKeys/2;
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return this.size == 0;
    }

    public boolean containsKey(Object key) {

        Pair<Key, Value> P1 = table1.get(getIndex((Key) key, h1));
        Pair<Key, Value> P2 = table2.get(getIndex((Key) key, h2));

        return (P1 != null && P1.getKey().equals(key))
                || (P2 != null && P2.getKey().equals(key));
    }

    public boolean containsValue(Object value) {
        return false;
    }

    public Value get(Object key) {
        try {
            Key mKey = (Key) key;

            if (table1.get(getIndex(mKey, h1)) != null) {
                Key k1 = table1.get(getIndex(mKey, h1)).getKey();
                if (mKey.equals(k1)) {
                    return table1.get(getIndex(k1, h1)).getValue();
                }
            }

            if (table2.get(getIndex(mKey, h2)) != null) {
                Key k2 = table2.get(getIndex(mKey, h2)).getKey();
                if (mKey.equals(k2)) {
                    return table2.get(getIndex(k2, h2)).getValue();
                }
            }
        }
        catch (Exception e){
            e.printStackTrace();
            System.out.println("Argument invalide");
        }

        return null;
    }

    public Value put(Key key, Value value) {
        int counter = 0;
        size++;

        try {
            putT1(key, value, counter);
        } catch (Exception e) {
            e.printStackTrace();
        }
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

    public Value remove(Object key) {
        Key mKey = (Key) key;

        if (table1.get(getIndex(mKey, h1)) != null) {
            Key k1 = table1.get(getIndex(mKey, h1)).getKey();
            if (mKey.equals(k1)) {
                table1.set(getIndex(k1, h1), null);
                size--;
            }
        }

        if (table2.get(getIndex(mKey, h2)) != null) {
            Key k2 = table2.get(getIndex(mKey, h2)).getKey();
            if (mKey.equals(k2)) {
                table2.set(getIndex(k2, h2), null);
                size--;
            }
        }
    }

    public void putAll(Map<? extends Key, ? extends Value> m) {

    }

    public void clear() {

    }

    public Set<Key> keySet() {
        return null;
    }

    public Collection<Value> values() {
        return null;
    }

    public Set<Entry<Key, Value>> entrySet() {
        return null;
    }

    private int getIndex(Key key, int seed) {
        return Math.abs((int) key.hashCode(seed) % table1.size());
    }

}
