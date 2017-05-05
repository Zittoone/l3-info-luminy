package fr.licinfo;

import edu.stanford.nlp.ling.CoreLabel;
import edu.stanford.nlp.parser.lexparser.LexicalizedParser;
import edu.stanford.nlp.pipeline.StanfordCoreNLP;
import edu.stanford.nlp.process.CoreLabelTokenFactory;
import edu.stanford.nlp.process.PTBTokenizer;
import edu.stanford.nlp.process.Tokenizer;
import edu.stanford.nlp.process.TokenizerFactory;
import edu.stanford.nlp.trees.Tree;
import edu.stanford.nlp.trees.TreePrint;
import javafx.util.Pair;
import sun.plugin2.message.PrintAppletReplyMessage;

import java.io.StringReader;
import java.util.List;

/**
 * Created by Alexis Couvreur on 23/04/2017.
 */
public class Parser {
    private TokenizerFactory<CoreLabel> tokenizerFactory = PTBTokenizer.factory(new CoreLabelTokenFactory(), "invertible=true");

    private LexicalizedParser parser;

    private Parser(){
    }

    public Parser(String url){
        parser = LexicalizedParser.loadModel(url);
    }

    public Tree parse(String str) {
        List<CoreLabel> tokens = tokenize(str);
        return parser.apply(tokens);
    }

    private List<CoreLabel> tokenize(String str) {
        Tokenizer<CoreLabel> tokenizer =
                tokenizerFactory.getTokenizer(
                        new StringReader(str));
        return tokenizer.tokenize();
    }
}
