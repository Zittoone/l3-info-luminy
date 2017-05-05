package fr.licinfo;

import edu.stanford.nlp.ling.*;
import edu.stanford.nlp.parser.nndep.DependencyParser;
import edu.stanford.nlp.process.DocumentPreprocessor;
import edu.stanford.nlp.process.Morphology;
import edu.stanford.nlp.tagger.maxent.MaxentTagger;
import edu.stanford.nlp.trees.GrammaticalStructure;
import edu.stanford.nlp.trees.Tree;
import org.maltparser.concurrent.ConcurrentMaltParserModel;
import org.maltparser.concurrent.ConcurrentMaltParserService;
import org.maltparser.concurrent.graph.ConcurrentDependencyGraph;
import org.maltparser.core.exception.MaltChainedException;

import java.io.File;
import java.io.IOException;
import java.io.Reader;
import java.io.StringReader;
import java.net.MalformedURLException;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

/**
 * @author Alexis Couvreur
 *
 */
public class YodaTranslater {

    private final static String PARSER_MODEL = "/org/maltparser/fremalt-1.7.mco";

    private Parser parser;
    private YodaGrammar yGrammar;
    private ConcurrentMaltParserModel parserModel;

    private YodaTranslater(){}

    public YodaTranslater(String parserUrl, String maltParserUrl){

        yGrammar = new YodaGrammar();
        try {
            parser = new Parser(parserUrl);
            // parserModel = ConcurrentMaltParserService.initializeParserModel(this.getClass().getResource(PARSER_MODEL));
            parserModel = ConcurrentMaltParserService.initializeParserModel(new File(maltParserUrl));
        } catch (MaltChainedException e) {
            e.printStackTrace();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
    }

    public String translate(final String text) {
        if(text.length() > 85)
            return text;

        StringBuilder translatedText = new StringBuilder();

        /* 1. Découper le texte entrant et le traiter phrase par phrase */
        List<String> sentences = textToSentences(text);

        /* 2. On traite les phrases une à une */
        sentences.forEach((String sentence) -> {
            StringBuilder translatedSentence = new StringBuilder();

            /* 3. On traite chaque segment SVO et on les transforme en OSV */

            /* On tokenize la phrase */
            Tree tree = parser.parse(sentence);

            /* On utilise maltParser */
            // The malt parser requires token in the MaltTab format (Connll).
            // Instead of using the Stanford tagger, we could have used Melt or another parser.
            String[] tokens = getMaltTabFormat(tree);
            ConcurrentDependencyGraph graph = null;
            try {
                graph = parserModel.parse(tokens);
            } catch (MaltChainedException e) {
                e.printStackTrace();
                return;
            }

            /* On fait appel à la grammaire et on lui passe le graph */
            translatedSentence.append(yGrammar.axiome(graph, sentence));

            /* On ajoute la plhrase au texte final */
            translatedText.append(translatedSentence.toString());
        });

        // System.out.println(translatedText.toString());
        return translatedText.toString();
    }

    private String[] getMaltTabFormat(Tree tree) {
        return tree.taggedLabeledYield().stream()
                .map(word -> {
                    CoreLabel w = (CoreLabel)word;
                    String lemma = Morphology.lemmatizeStatic(new WordTag(w.word(), w.tag())).word();
                    String tag = w.value();

                    return String.join("\t", new String[]{
                            String.valueOf(w.index()+1),
                            w.word(),
                            lemma != null ? lemma : w.word(),
                            tag != null ? String.valueOf(tag.charAt(0)) : "_",
                            tag != null ? tag : "_"
                    });
                })
                .toArray(String[]::new);
    }

    private List<String> textToSentences(String text) {
        Reader reader = new StringReader(text);
        DocumentPreprocessor dp = new DocumentPreprocessor(reader);
        List<String> sentenceList = new ArrayList<>();

        for (List<HasWord> sentence : dp) {
            // On utilise SentenceUtils
            String sentenceString = SentenceUtils.listToString(sentence);
            sentenceList.add(sentenceString);
        }

        return sentenceList;
    }
}