package fr.licinfo;

import org.annolab.tt4j.TokenHandler;
import org.annolab.tt4j.TreeTaggerWrapper;

import static java.util.Arrays.asList;

public class App
{
    public static void main( String[] args ) throws Exception {



        System.setProperty("treetagger.home", "c:\\TreeTagger");
        TreeTaggerWrapper tt = new TreeTaggerWrapper<String>();
        try {
            tt.setModel("c:\\TreeTagger\\lib\\french-utf8.par:iso8859-1");
            tt.setHandler(new TokenHandler<String>() {
                public void token(String token, String pos, String lemma) {
                    System.out.println(token + "\t" + pos + "\t" + lemma);
                }
            });
            tt.process(asList(new String[] { "Il", "est", "ton", "père", "." }));
        }
        finally {
            tt.destroy();
        }
    }
}
