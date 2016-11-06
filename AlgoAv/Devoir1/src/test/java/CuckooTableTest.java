import org.junit.Test;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.*;

/**
 * Created by Alexis Couvreur on 27/10/2016.
 */
public class CuckooTableTest {

    @Test
    public void isEmpty() throws Exception {
        CuckooTable<HashableString, Integer> ct = new CuckooTable<HashableString, Integer>(5);

        assertThat(ct.isEmpty(), equalTo(true));
    }

    @Test
    public void put() throws Exception {
        CuckooTable<HashableString, Integer> ct = new CuckooTable<HashableString, Integer>(5);

        HashableString bananes = new HashableString("bananes");

        ct.put(bananes, 21);

        assertThat(ct.isEmpty(), equalTo(false));
    }

    @Test
    public void containsKey() throws Exception {
        CuckooTable<HashableString, Integer> ct = new CuckooTable<HashableString, Integer>(5);

        HashableString bananes = new HashableString("bananes");

        // Autre instance d'objet avec même contenu afin de vérifier que
        // la comparaison ne fonctionne pas par adresse d'objet
        HashableString bananes2 = new HashableString("bananes");

        ct.put(bananes, 21);

        assertThat(ct.containsKey(bananes2), equalTo(true));
    }

    @Test
    public void get() throws Exception {
        CuckooTable<HashableString, Integer> ct = new CuckooTable<HashableString, Integer>(5);

        HashableString bananes = new HashableString("bananes");

        // Autre instance d'objet avec même contenu afin de vérifier que
        // la comparaison ne fonctionne pas par adresse d'objet
        HashableString bananes2 = new HashableString("bananes");

        ct.put(bananes, 21);

        Integer result = ct.get(bananes2);

        assertThat(result, equalTo(21));
    }



    @Test
    public void remove() throws Exception {
        CuckooTable<HashableString, Integer> ct = new CuckooTable<HashableString, Integer>(5);

        HashableString bananes = new HashableString("bananes");

        // Autre instance d'objet avec même contenu afin de vérifier que
        // la comparaison ne fonctionne pas par adresse d'objet
        HashableString bananes2 = new HashableString("bananes");

        ct.put(bananes, 21);

        ct.remove(bananes);

        Integer result = ct.get(bananes2);

        assertThat(result, equalTo(null));

    }

}