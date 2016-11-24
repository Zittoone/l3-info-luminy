import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Created by Alexis Couvreur on 16/11/2016.
 */
public class Trigramme {

    /**
     * <code>dictionnary</code> est un HashMap tel que :
     * <code>Key</code> : est un <code>String</code> qui est un trigramme
     * <code>Value</code> : est un <code>Set</code> qui contient les mots contenant ce même trigramme
     */
    private Map<String, Set<String>> dictionnary;

    /**
     * Création d'une instance d'un Trigramme en initialisant <var>dictionnary</var>
     */
    public Trigramme(){
        dictionnary = new HashMap<String, Set<String>>();
    }

    /**
     * Ajout d'un mot dans le dictionnaire, en plusieurs étapes :
     *  1) Vérification si le mot peut contenir au moins un trigramme, sinon on arrête.
     *  2) Si l'étape 1 passe, on ajoute un caractère spécial "<" au début, et ">" à la fin.
     *  3) On le découpe en trigramme et on ajoute chacun des trigrammes dans le dictionnaire
     *      avec le mot dans la liste de la clé.
     * @param word
     */
    public void addWord(String word){

        // Si il contient au moins un triplet
        if(word.length() < 3)
            return;

        // On ajoute les caractères spécieaux
        String wordWithSpeChar = "<" + word + ">";

        for(int i = 0; i < wordWithSpeChar.length() - 2; i++){
            // Si le trigram n'existe pas, on initialise un set avec une valeur
            dictionnary.putIfAbsent(wordWithSpeChar.substring(i, i+3), new HashSet<String>());
            dictionnary.get(wordWithSpeChar.substring(i, i+3)).add(word);
        }
    }

    /**
     * <code>executeProcess</code> est une fonction permettant de mettre en oeuvre le scénario décrit dans le Devoir 2.
     * On initialise le dictionnaire, et on suit étape par étape, et on donne les résultats possibles.
     * @param word le mot à corriger
     * @return une liste de propositions classé dans l'ordre du plus probable au moins (par la distance de Levenshtein dans l'ordre croissant)
     */
    public List<String> executeProcess(String word){

        // Contiendra les propositions de correction
        List<String> propositions = new LinkedList<String>();

        System.out.println("\nÉtape 1");
        System.out.println("Vérification de la présence de " + word + " dans le dictionnaire...");
        long debut = System.currentTimeMillis();
        //
        // Etape 1
        //
        // On regarde si le mot est dans le dictionnaire
        if(isWordContained(word)){
            System.out.println("Le mot est contenu dans le dictionnaire. Fin du programme. (" + (System.currentTimeMillis() - debut) + " ms)");
            propositions.add(word);
            // On retourne la liste contenant un seul élément, le mot lui même
            return propositions;
        }

        System.out.println("Le mot n'est pas contenu dans le dictionnaire. (" + (System.currentTimeMillis() - debut) + " ms)");

        System.out.println("\nÉtape 2");
        System.out.println("Création des trigrammes du mot " + word + "...");
        debut = System.currentTimeMillis();
        //
        // Etape 2
        //
        // Le mot n'est pas dans le dictionnaire, on construit les trigrammes du dictionnaires
        // et celui du mot a corriger
        List<String> trigramsWord = new LinkedList<>();
        word = "<" + word + ">";

        for(int i = 0; i < word.length() - 2; i++){
            trigramsWord.add(word.substring(i, i+3));
        }
        System.out.println("Les trigrammes ont été créés (" + (System.currentTimeMillis() - debut) + " ms) -> \n" + trigramsWord.toString());


        System.out.println("\nÉtape 3");
        System.out.println("Création de la liste des mots contenant les trigrammes de " + word + "...");
        debut = System.currentTimeMillis();
        //
        // Etape 3
        //
        // On va regarder pour chaque trigramme la liste de mot contenant ce trigramme
        Map<String, Integer> wordsList = initializeWordMap(trigramsWord);
        System.out.println("Les mots ont été récupérés, passage à l'étape suivante pour filtrer les résultats (" + (System.currentTimeMillis() - debut) + " ms)");


        System.out.println("\nÉtape 4");
        System.out.println("Triage de la liste des mots contenant les trigrammes de " + word + "...");
        debut = System.currentTimeMillis();
        //
        // Etape 4
        //
        // On va trier ce nouveau HashMap en fonction de ses valeurs et on gardera les plus hautes
        wordsList = sortByValue(wordsList, 10, true);
        System.out.println("Les mots ont été triés (" + (System.currentTimeMillis() - debut) + " ms) ->  <mot> = <nombre de trigramme en commun>\n" + wordsList.toString());

        System.out.println("\nÉtape 5");
        System.out.println("Application de la distance de Levenshtein sur la liste triée...");
        debut = System.currentTimeMillis();
        //
        // Etape 5
        //
        // on calcule la distance d’édition de chacun avec le mot à corriger, on garde les meilleurs, triés dans
        // l’ordre de distance d’édition. Le premier est notre proposition, mais peut-être la bonne solution
        // n’est placée que 2e ou 3e, donc on donne une liste des meilleurs choix à l’utilisateur pour qu’il
        // choisisse celle qu’il préfère.
        wordsList = getBestSolutions(word, wordsList.keySet());
        System.out.println("Les mots ont été triés (" + (System.currentTimeMillis() - debut) + " ms) -> <mot> = <distance de levenshtein entre le mot proposé et le mot correct> \n" + wordsList.toString());

        propositions.addAll(wordsList.keySet());

        return propositions;
    }

    /**
     * <code>initializeDictionnary</code> va initialisé <var>dictionnary</var> par rapport au fichier donné en paramètre.
     * Il va itérer ligne par ligne en ajoutant chaque mot au dictionnaire.
     * @param f
     */
    public void initializeDictionnary(File f){

        System.out.println("Initialisation du dictionnaire, traitement du fichier \"" + f.getName() + "\"");
        long debut = System.currentTimeMillis();
        try {

            BufferedReader bufferedReader = new BufferedReader(new FileReader(f));
            String mot = bufferedReader.readLine();

            while (mot != null) {
                this.addWord(mot);
                mot = bufferedReader.readLine();
            }

            bufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Dictionnaire initialisé. (" + (System.currentTimeMillis() - debut) + " ms)");
    }

    /**
     * Pour vérifier si un mot est contenu dans un dictionnaire
     * il suffit de regarder si le mot est dans le set de l'un de ses trigrammes
     * @param word
     * @return
     */
    public boolean isWordContained(String word){
        // Mot ne contenant pas de trigramme
        if(word.length() < 3)
            return false;

        // On créé un trigramme
        String trigram = word.substring(0, 3);

        // Si le trigramme est présent et si le mot est contenu
        return dictionnary.containsKey(trigram) && dictionnary.get(trigram).contains(word);
    }

    /**
     * Le but de cette méthode est de renvoyer un LinkedHashMap tel que :
     *  <code>Key</code> : Un élément de <var>words</var>
     *  <code>Value</code> : La distance de levenshtein entre sa clé et <var>word</var>
     * trié par ordre croissant, donc de la plus petite distance d'édition à la plus grande.
     * @param word Le mot à corriger
     * @param words Un set de mot à proposer en correction à <var>word</var>
     * @return LinkedHashMap trié en fonction de Levenshtein.
     */
    private Map<String, Integer> getBestSolutions(String word, Set<String> words) {
        Map<String, Integer> wordsWithLevenshtein = new HashMap<>();
        for (String str : words) {
            wordsWithLevenshtein.put(str, Levenshtein.levenshteinDistance(word, str));
        }
        return sortByValue(wordsWithLevenshtein, 5, false);
    }

    /**
     * Le but est d'initialiser une <code>Map</code> tel que,
     * pour chaque trigrammes du mot à corriger (<var>trigramsWord</var>)
     * On va ajouter tous les mots contenant le trigramme itéré,
     * et ajouter en tant que valeur à la clé, son nombre d'occurrence
     * @param trigramsWord Une <code>List</code> de trigramme du mot à corriger
     * @return Un HashMap avec une association Mot -> Nombre de trigramme en commun
     */
    private Map<String, Integer> initializeWordMap(List<String> trigramsWord) {
        Map<String, Integer> map = new HashMap<>();
        for (String trig : trigramsWord) {
            if(dictionnary.containsKey(trig)){
                for (String word : dictionnary.get(trig)) {
                    map.putIfAbsent(word, 0);
                    map.put(word, map.get(word) + 1);
                }
            }
        }
        return map;
    }


    /**
     * Code original : <url>https://www.mkyong.com/java/how-to-sort-a-map-in-java/</url>
     * J'ai modifié le code et ajouté 2 paramètre afin de pouvoir moduler le résultat en fonction des attentes.
     * @param unsortMap Un <code>Map</code> non trié
     * @param maxElements Le nombre max d'élément dans notre <code>Map</code> retourné
     * @param desc Trié de manière décroissante ou non.
     * @return <code>LinkedHashMap</code> trié en fonction de <var>desc</var> avec au maximum <var>maxElements</var> éléments.
     */
    private static Map<String, Integer> sortByValue(Map<String, Integer> unsortMap, Integer maxElements, boolean desc) {

        // 1. Convert Map to List of Map
        List<Map.Entry<String, Integer>> list =
                new LinkedList<Map.Entry<String, Integer>>(unsortMap.entrySet());

        // 2. Sort list with Collections.sort(), provide a custom Comparator
        //    Try switch the o1 o2 position for a different order
        if(desc)
            Collections.sort(list, (o1, o2) -> (o2.getValue()).compareTo(o1.getValue()));
        else Collections.sort(list, (o1, o2) -> (o1.getValue()).compareTo(o2.getValue()));

        // 3. Loop the sorted list and put it into a new insertion order Map LinkedHashMap
        Map<String, Integer> sortedMap = new LinkedHashMap<String, Integer>();
        for (Map.Entry<String, Integer> entry : list) {
            sortedMap.put(entry.getKey(), entry.getValue());

            if(sortedMap.size() > maxElements)
                break;
        }


        return sortedMap;
    }
}
