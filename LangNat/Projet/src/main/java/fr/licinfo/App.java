package fr.licinfo;

import edu.stanford.nlp.ling.CoreLabel;
import edu.stanford.nlp.ling.WordTag;
import edu.stanford.nlp.parser.lexparser.LexicalizedParser;
import edu.stanford.nlp.process.*;
import edu.stanford.nlp.trees.Tree;
import org.maltparser.concurrent.ConcurrentMaltParserModel;
import org.maltparser.concurrent.ConcurrentMaltParserService;
import org.maltparser.concurrent.graph.ConcurrentDependencyGraph;
import org.maltparser.core.exception.MaltChainedException;

import java.io.File;
import java.io.StringReader;
import java.net.MalformedURLException;
import java.util.List;
import java.util.Scanner;

/**
 * Created by Alexis Couvreur on 23/04/2017.
 */
public class App {

    public static void main(String[] args) throws MalformedURLException, MaltChainedException {

        if(args.length != 2){
            System.err.println("Syntaxe : pathToLLexicalizedParserModel pathToMaltParserFrenchMco");
        }
        YodaTranslater yodaConverter = new YodaTranslater(args[0], args[1]);
        Scanner scanner = new Scanner(System.in);
        String line;

        System.out.println("Entrez une phrase :");
        System.out.print("> ");
        while((line = scanner.nextLine()).length() > 0){
            // yodaConverter.printDependencies(line);
            System.out.println(yodaConverter.translate(line));
            System.out.println("\nEntrez une phrase (vide pour arrêter) :");
            System.out.print("> ");
        }
    }
}
