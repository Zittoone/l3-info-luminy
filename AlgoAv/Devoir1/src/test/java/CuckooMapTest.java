import org.junit.Test;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 31/10/2016.
 */
public class CuckooMapTest {

    @Test
    public void size() throws Exception {
        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.size(), equalTo(0));

        HashableString hs = new HashableString("Test");

        ct.put(hs, 1);
        ct.put(hs, 1);

        assertThat(ct.size(), equalTo(1));

    }

    @Test
    public void isEmpty() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.isEmpty(), equalTo(true));

        HashableString hs = new HashableString("Test");

        ct.put(hs, 1);
        ct.put(hs, 1);

        assertThat(ct.isEmpty(), equalTo(false));
    }

    @Test
    public void containsKey() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.size(), equalTo(0));

        HashableString hs = new HashableString("Test");
        HashableString hs2 = new HashableString("test");

        ct.put(hs, 1);
        ct.put(hs, 1);

        assertThat(ct.containsKey(hs), equalTo(true));
        assertThat(ct.containsKey(hs2), equalTo(false));
    }

    @Test
    public void containsValue() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.size(), equalTo(0));

        HashableString hs = new HashableString("Test");

        ct.put(hs, 1);
        ct.put(hs, 1);

        assertThat(ct.containsValue(1), equalTo(true));
        assertThat(ct.containsValue(4), equalTo(false));
    }

    @Test
    public void get() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.size(), equalTo(0));

        HashableString hs = new HashableString("Test");
        HashableString hs2 = new HashableString("test");

        ct.put(hs, 1);

        assertThat(ct.get(hs), equalTo(1));
        assertThat(ct.get(hs2), equalTo(null));
    }

    @Test
    public void put() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.size(), equalTo(0));

        HashableString hs = new HashableString("Test");

        assertThat(ct.put(hs, 1), equalTo(null));
        assertThat(ct.put(hs, 1), equalTo(1));
    }

    @Test
    public void putAll() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);
        Map<HashableString, Integer> mp = new HashMap<HashableString, Integer>(5);

        HashableString hs1 = new HashableString("Test1");
        HashableString hs2 = new HashableString("Test2");
        HashableString hs3 = new HashableString("Test3");

        mp.put(hs1, 1);
        mp.put(hs2, 2);
        mp.put(hs3, 3);

        assertThat(ct.size(), equalTo(0));

        ct.putAll(mp);

        assertThat(ct.size(), equalTo(3));

    }

    @Test
    public void clear() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);

        assertThat(ct.size(), equalTo(0));

        HashableString hs = new HashableString("Test");

        ct.put(hs, 4);

        assertThat(ct.size(), equalTo(1));

        ct.clear();

        assertThat(ct.size(), equalTo(0));

    }

    @Test
    public void keySet() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);
        Set<HashableString> keyset;

        HashableString hs = new HashableString("Test");

        ct.put(hs, 1);

        keyset = ct.keySet();

        assertThat(keyset.toString(), equalTo("[Test]"));
    }

    @Test
    public void values() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);
        Collection<Integer> values;

        HashableString hs = new HashableString("Test");

        ct.put(hs, 1);

        values = ct.values();

        assertThat(values.toString(), equalTo("[1]"));
    }

    @Test
    public void entrySet() throws Exception {

        CuckooMap<HashableString, Integer> ct = new CuckooMap<HashableString, Integer>(5);
        Set<Map.Entry<HashableString, Integer>> entrySet;

        HashableString hs = new HashableString("Test");

        ct.put(hs, 1);

        entrySet = ct.entrySet();

        assertThat(entrySet.toString(), equalTo("[Test=1]"));
    }

}