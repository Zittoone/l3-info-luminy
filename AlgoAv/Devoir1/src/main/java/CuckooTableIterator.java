import javafx.util.Pair;

import java.util.*;
import java.lang.Object;

/**
 * Created by Alexis Couvreur on 27/10/2016.
 */
public class CuckooTableIterator<Key extends FamilyHashable, Value> implements Iterator {

    private int cursor;
    private List<Key> entries;
    private CuckooTable<Key, Value> ct;

    public CuckooTableIterator(CuckooTable<Key, Value> ct){
        cursor = 0;
        this.ct = ct;

        entries = new ArrayList<Key>();

        // Génération du tableau d'entries

        Vector<Pair<Key, Value>> v1 = ct.getTable1();
        Vector<Pair<Key, Value>> v2 = ct.getTable2();

        Pair<Key, Value> temp;
        for(int i = 0; i <= ct.size(); i++){
            temp = v1.get(i);

            if(temp != null)
                entries.add(temp.getKey());

            temp = v2.get(i);

            if(temp != null)
                entries.add(temp.getKey());
        }
    }

    public boolean hasNext() {
        return cursor != ct.size();
    }

    public Value next() {
        return ct.get(entries.get(cursor++));
    }

    public void remove() {

    }
}
