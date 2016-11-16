import devoir1.HashableString;
import org.junit.Test;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.assertThat;

/**
 * Created by Base on 16/11/2016.
 */
public class LevenshteinTest {

    @Test
    public void levenshteinDistance() throws Exception {
        Levenshtein levenshtein = new Levenshtein(null);

        assertThat(levenshtein.levenshteinDistance("Test", "Toast"), equalTo(2));
        assertThat(levenshtein.levenshteinDistance("LongString", "ShortStr"), equalTo(7));
        assertThat(levenshtein.levenshteinDistance("Test", "Test"), equalTo(0));
        assertThat(levenshtein.levenshteinDistance("", "Toast"), equalTo(5));
        assertThat(levenshtein.levenshteinDistance("Test", ""), equalTo(4));
        assertThat(levenshtein.levenshteinDistance("C", "CC"), equalTo(1));
    }

}
