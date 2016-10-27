import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Created by c16017548 on 21/09/16.
 */
public class PrefixTree<Value> {

    /**
     * Racine
     */
    private Node<Value> root;

    public PrefixTree() {
        this.root = new Node<Value>();
    }

    public boolean isEmpty() {
        return this.root.getChildren().isEmpty();
    }

    public boolean containsKey(String word) {
        Node<Value> node = root;
        for(int i = 0; i < word.length(); i++){
            HashableString hs = new HashableString(Character.toString(word.charAt(i)));
            node = node.getChildren().get(hs);
            if(node == null) return false;
        }
        
        return node.getWord() != null;
    }

    public Value get(String word) {
        Node<Value> node = root;
        for(int i = 0; i < word.length(); i++){
            HashableString hs = new HashableString(Character.toString(word.charAt(i)));
            node = node.getChildren().get(hs);
            if(node == null) return null;
        }

        return node.getWord();
    }

    public void put(String word, Value value) {
        Node<Value> node = root;

        for(int i = 0; i < word.length(); i++){

            // Si il n'y a pas la clé recherché on la créée
            HashableString currKey = new HashableString(Character.toString(word.charAt(i)));

            if(node.isEmpty() || !node.containsKey(currKey)){
                node.put(currKey, new Node(currKey));
            }

            // On récupère la clé suivante, qui vient soit d'être insérée
            // soit existait déjà.
            node = node.getChildren().get(currKey);
        }

        // On ajoute le mot
        node.setWord(value);
    }

    public void remove(String word) {
        Node<Value> node = root;
        for(int i = 0; i < word.length(); i++){
            HashableString hs = new HashableString(Character.toString(word.charAt(i)));
            node = node.getChildren().get(hs);
            if(node == null) return;
        }

        node.setWord(null);

    }

    // ----- S U P P L E M E N T ----- //
    public List<Value> findAllCombinations(String str, boolean useAllLetters){

        // Lancement récurssif
        return findAllCombinationsRec(root, str, useAllLetters);
    }

    private List<Value> findAllCombinationsRec(Node<Value> node, String str, boolean useAllLetters){
        List<Value> list = new ArrayList<Value>();

        // Si le noeud est nul, on arrête la recherche
        if(node == null)
            return list;

        // Si le noeud EST un mot
        if(node.getWord() != null){

            // Si on cherche un mot en utilisant TOUTES les lettres
            if(useAllLetters){
                // On fait la vérification
                if(str.length() == 0){
                    list.add(node.getWord());
                }
            } else {
                list.add(node.getWord());
            }

        }

        for(int i = 0; i < str.length(); i++){

            HashableString hs = new HashableString(Character.toString(str.charAt(i)));
            System.out.print("Lancement récursif pour le caractère : " + hs.toString());

            StringBuilder sb = new StringBuilder(str);
            sb.deleteCharAt(i);

            String newStr = sb.toString();
            System.out.println(" avec comme nouvelle chaîne -> " + newStr);

            list.addAll(findAllCombinationsRec(node.getChildren().get(hs), newStr, useAllLetters));
        }

        return list;
    }

}