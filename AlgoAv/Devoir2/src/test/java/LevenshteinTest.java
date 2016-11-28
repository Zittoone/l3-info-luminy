import org.junit.Test;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.assertThat;

/**
 * Created by Base on 16/11/2016.
 */
public class LevenshteinTest {

    @Test
    public void levenshteinDistance() throws Exception {

        assertThat(Levenshtein.levenshteinDistance("Test", "Toast"), equalTo(2));
        assertThat(Levenshtein.levenshteinDistance("LongString", "ShortStr"), equalTo(7));
        assertThat(Levenshtein.levenshteinDistance("Test", "Test"), equalTo(0));
        assertThat(Levenshtein.levenshteinDistance("", "Toast"), equalTo(5));
        assertThat(Levenshtein.levenshteinDistance("Test", ""), equalTo(4));
        assertThat(Levenshtein.levenshteinDistance("C", "CC"), equalTo(1));
    }

}
