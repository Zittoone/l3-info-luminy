package fr.licinfo;

import edu.stanford.nlp.trees.Tree;
import org.maltparser.concurrent.graph.ConcurrentDependencyGraph;

import static fr.licinfo.Premier.GN;

/**
 * Created by Alexis Couvreur on 23/04/2017.
 *
 * Grammaire Hors-Contexte
 * phrase -> GN GV
 * GN -> DET NOM
 * GV -> V GV
 * V -> ...
 * DET -> ...
 *
 *
 *
 */
public class YodaGrammar {


    public YodaGrammar(){}

    /**
     * phrase -> VN
     * @param root
     * @return
     */
    public String axiome(ConcurrentDependencyGraph root, String sentence){

        StringBuilder stringBuilder = new StringBuilder();

        if(!root.hasTokens() || root.nTokenNodes() < 2)
            return sentence;


        try {
            stringBuilder.append(Predicate(root))
                    .append(", ")
                    .append(GN(root))
                    .append(Punctuation(root));

        } catch (InvalidSentenceException e){
            return sentence;
        }

        return sanitize(stringBuilder.toString());
    }


    /**
     * Dans le format SVO le sujet est tout le temps au début
     * D N |
     * D N A |
     * D N P N
     * @param child
     * @return
     * @throws InvalidSentenceException
     */
    private String GN(ConcurrentDependencyGraph child) throws InvalidSentenceException {
        StringBuilder sb = new StringBuilder();

        if(GN.estPremier(child.getTokenNode(1).getLabel(3))){
            for(int i = 1; i < child.nTokenNodes() + 1; i++){
                sb.append(" ").append(child.getTokenNode(i).getLabel(1));

                if(child.getTokenNode(i).getLabel(7).equals("root")){
                    break;
                }
            }
        } else {
            throw new InvalidSentenceException(child.getTokenNode(1).getLabel(3) + " is not primary of GN");
        }
        return sb.toString();
    }

    private String Predicate(ConcurrentDependencyGraph child) throws InvalidSentenceException {
        StringBuilder sb = new StringBuilder();
        boolean predicate = false;
            for(int i = 1; i < child.nTokenNodes()  + 1; i++){
                if(child.getTokenNode(i).getLabel(1).equals("."))
                    break;
                if(predicate)
                    sb.append(" ").append(child.getTokenNode(i).getLabel(1));
                if(child.getTokenNode(i).getLabel(7).equals("root"))
                    predicate = true;
            }
        return sb.toString();
    }

    private String Punctuation(ConcurrentDependencyGraph child) {
        return ".";
    }

    private static String sanitize(String s) {
        if(s.length() == 0)
            return s;
        /* On enlève les espaces avants et après */
        s = s.trim();
        /* Tout en minuscule */
        s = s.toLowerCase();
        /* On supprime l'espace avant chaque ponctuation */
        s = s.replaceAll("\\s\\s", " ");
        s = s.replaceAll("\\s`\\s", "'");
        s = s.replaceAll("\\s+(?=[),.'])", "");
        /* On met la majuscule devant */
        s = Character.toUpperCase(s.charAt(0)) + s.substring(1);
        return s;
    }

    private static String retriveTextFromTree(Tree child) {
        if(child.isLeaf())
            return child.label().value();
        StringBuilder stringBuilder = new StringBuilder();
        for (Tree tree : child.children()) {
            stringBuilder.append(retriveTextFromTree(tree)).append(" ");
        }
        return stringBuilder.toString();
    }

    private void error(String reason){
        System.err.println(reason);
        System.exit(1);
    }

}
