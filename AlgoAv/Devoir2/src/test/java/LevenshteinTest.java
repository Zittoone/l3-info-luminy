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
        assertThat(Levenshtein.levenshteinDistance("soeur", "sœur"), equalTo(2));
    }

    @Test
    public void levenshteinFromPythonDistance() throws Exception {

        assertThat(Levenshtein.levenshteinFromPython("Test", "Toast"), equalTo(2));
        assertThat(Levenshtein.levenshteinFromPython("LongString", "ShortStr"), equalTo(7));
        assertThat(Levenshtein.levenshteinFromPython("Test", "Test"), equalTo(0));
        assertThat(Levenshtein.levenshteinFromPython("", "Toast"), equalTo(5));
        assertThat(Levenshtein.levenshteinFromPython("Test", ""), equalTo(4));
        assertThat(Levenshtein.levenshteinFromPython("C", "CC"), equalTo(1));
        assertThat(Levenshtein.levenshteinFromPython("soeur", "sœur"), equalTo(2));
    }

}
