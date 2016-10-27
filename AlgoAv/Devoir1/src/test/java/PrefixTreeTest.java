import org.junit.Test;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 27/10/2016.
 */
public class PrefixTreeTest {

    @Test
    public void isEmpty() throws Exception {
        PrefixTree<String> prefixTree = new PrefixTree<String>();

        assertThat(prefixTree.isEmpty(), equalTo(true));
    }

    @Test
    public void put() throws Exception {
        PrefixTree<String> prefixTree = new PrefixTree<String>();

        prefixTree.put("Bonjour", "Hello");

        assertThat(prefixTree.isEmpty(), equalTo(false));
    }

    @Test
    public void containsKey() throws Exception {
        PrefixTree<String> prefixTree = new PrefixTree<String>();

        prefixTree.put("Bonjour", "Hello");

        assertThat(prefixTree.containsKey("Bonjour"), equalTo(true));
    }

    @Test
    public void get() throws Exception {
        PrefixTree<String> prefixTree = new PrefixTree<String>();

        prefixTree.put("Bonjour", "Hello");

        assertThat(prefixTree.get("Bonjour"), equalTo("Hello"));
    }

    @Test
    public void remove() throws Exception {
        PrefixTree<String> prefixTree = new PrefixTree<String>();

        prefixTree.put("Bonjour", "Hello");

        prefixTree.remove("Bonjour");

        assertThat(prefixTree.get("Bonjour"), equalTo(null));
    }

}