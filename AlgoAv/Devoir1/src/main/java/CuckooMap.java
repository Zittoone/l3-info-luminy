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
            return putT1(key, value, counter);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private Value putT1(Key key, Value value, int counter) throws Exception {
        if (counter > MAX_ITERATION)
            throw new Exception("Echec");
        else {
            // Variable temporaire pointant sur la valeur de la case
            // renvoyant soit null, soit l'ancienne valeur
            Pair<Key, Value> pair = table1.get(getIndex(key, h1));

            // Déjà occupé
            if (pair != null) {

                // S'il s'agit de la même clé, on remplace
                if(pair.getKey().equals(key)){
                    table1.set(getIndex(key, h1), new Pair<Key, Value>(key, value));
                }

                // Sinon, on déplace la Pair clé - valeur
                else {
                    table1.set(getIndex(key, h1), new Pair<Key, Value>(key, value));
                    counter++;

                    // On met dans le vector T2 la clé et la valeur
                    putT2(pair.getKey(), pair.getValue(), counter);
                }
            }

            // Non occupé
            else {
                table1.set(getIndex(key, h1), new Pair<Key, Value>(key, value));
                return null;
            }

            // pair n'est pas égal à null ici
            return pair.getValue();
        }
    }

    private Value putT2(Key key, Value value, int counter) throws Exception {

        // Variable temporaire pointant sur la valeur de la case
        // renvoyant soit null, soit l'ancienne valeur
        Pair<Key, Value> pair = table2.get(getIndex(key, h2));

        // Déjà occupé
        if (pair != null) {
            table2.set(getIndex(key, h2), new Pair<Key, Value>(key, value));
            counter++;
            putT1(pair.getKey(), pair.getValue(), counter);
        }

        // Non occupé
        else {
            table2.set(getIndex(key, h2), new Pair<Key, Value>(key, value));
            return null;
        }
        // pair n'est pas égal à null ici
        return pair.getValue();
    }

    public Value remove(Object key) {
        Key mKey = (Key) key;
        Value prevValue = null;

        Pair<Key, Value> tempPair;

        tempPair = table1.get(getIndex(mKey, h1));
        if (tempPair != null) {
            Key k1 = tempPair.getKey();
            if (mKey.equals(k1)) {
                prevValue = tempPair.getValue();
                table1.set(getIndex(k1, h1), null);
                size--;
            }
        }

        tempPair = table2.get(getIndex(mKey, h2));
        if (tempPair != null) {
            Key k2 = tempPair.getKey();
            if (mKey.equals(k2)) {
                prevValue = tempPair.getValue();
                table2.set(getIndex(k2, h2), null);
                size--;
            }
        }
        return prevValue;
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
