import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Created by Alexis Couvreur on 16/11/2016.
 */
public final class Trigramme {

    private Trigramme(){}

    public static List<String> getTrigrams(String mot){

        mot = "<" + mot + ">";

        List<String> trigrammes = new ArrayList<String>();
        int taille_mot = mot.length();

        // On test la longueur du mot
        if(taille_mot <= 3){
            trigrammes.add(mot);
        }

        else {
            for(int i = 0; i < taille_mot - 3; i++){
                trigrammes.add(mot.substring(i, i+3));
            }
        }

        return trigrammes;
    }


    public static List<String> executeProcess(String word, File f){

        // On initialise le hashmap, les valeurs des clés valent null
        // C'est un dictionnaire qui aura la forme Mot->Ses trigrammes
        Map<String, List<String>> dictionnary = initializeDictionnary(f);

        // Contiendra les propositions de correction
        List<String> propositions = new LinkedList<String>();


        //
        // Etape 1
        //
        // On regarde si le mot est dans le dictionnaire
        if(isWordContained(word, dictionnary)){
            propositions.add(word);
            // On retourne la liste contenant un seul élément, le mot lui même
            return propositions;
        }


        //
        // Etape 2
        //
        // Le mot n'est pas dans le dictionnaire, on construit les trigrammes du dictionnaires
        // et celui du mot a corriger
        buildDictionnary(dictionnary);
        List<String> trigramsWord = getTrigrams(word);


        //
        // Etape 3
        //
        // On va regarder pour chaque trigramme la liste de mot contenant ce trigramme
        Map<String, Integer> wordsList = initializeWordsList(trigramsWord, dictionnary);


        //
        // Etape 4
        //
        // On va trier ce nouveau HashMap en fonction de ses valeurs et on gardera les plus hautes
        wordsList = sortByValue(wordsList, 100);


        //
        // Etape 5
        //
        // on calcule la distance d’édition de chacun avec le mot à corriger, on garde les meilleurs, triés dans
        // l’ordre de distance d’édition. Le premier est notre proposition, mais peut-être la bonne solution
        // n’est placée que 2e ou 3e, donc on donne une liste des meilleurs choix à l’utilisateur pour qu’il
        // choisisse celle qu’il préfère.
        propositions.addAll(getBestSolutions(word, wordsList).keySet());

        return propositions;
    }

    private static Map<String, Integer> getBestSolutions(String word, Map<String, Integer> wordsList) {
        Map<String, Integer> propositions = new HashMap<>();
        // wordsList est trié dans l'ordre décroissant
        for (Map.Entry<String, Integer> entry : wordsList.entrySet()) {
            propositions.put(entry.getKey(), Levenshtein.levenshteinDistance(word, entry.getKey()));
        }

        // On trie, et on garde les 2 à 3 meilleurs soluions
        propositions = sortByValue(propositions, 3);

        return propositions;
    }

    private static Map<String, Integer> sortByValue(Map<String, Integer> unsortMap, Integer maxElements) {

        // 1. Convert Map to List of Map
        List<Map.Entry<String, Integer>> list =
                new LinkedList<Map.Entry<String, Integer>>(unsortMap.entrySet());

        // 2. Sort list with Collections.sort(), provide a custom Comparator
        //    Try switch the o1 o2 position for a different order
        Collections.sort(list, (o1, o2) -> (o1.getValue()).compareTo(o2.getValue()));

        // 3. Loop the sorted list and put it into a new insertion order Map LinkedHashMap
        Map<String, Integer> sortedMap = new LinkedHashMap<String, Integer>();
        for (Map.Entry<String, Integer> entry : list) {
            sortedMap.put(entry.getKey(), entry.getValue());

            if(sortedMap.size() == maxElements)
                break;
        }

        return sortedMap;
    }

    private static Map<String,Integer> initializeWordsList(List<String> trigramsWord, Map<String, List<String>> dictionnary) {
        Map<String, Integer> hm = new HashMap<>();

        // Pour chaque trigrammes du mot à corriger
        for (String trigram : trigramsWord) {

            // On va faire un test sur chacun des trigrammes des mots du dictionnaire
            for (Map.Entry<String, List<String>> dicoEntry : dictionnary.entrySet()) {

                // Si dans la lste des trigrammes d'un mot, celui ci contient le trigramme itérer
                if (dicoEntry.getValue().contains(trigram)) {

                    // Alors on l'ajoute dans notre HashMap
                    if (hm.get(dicoEntry.getKey()) == null) {
                        // Si il n'était pas présent avant on l'initialise à 1
                        hm.put(dicoEntry.getKey(), 1);
                    } else {
                        hm.put(dicoEntry.getKey(), hm.get(dicoEntry.getKey()) + 1);
                    }
                }

            }
        }

        return hm;
    }

    private static void buildDictionnary(Map<String, List<String>> dictionnary) {
        for (Map.Entry<String, List<String>> entry : dictionnary.entrySet()) {
            entry.setValue(getTrigrams(entry.getKey()));
        }
    }


    public static boolean isWordContained(String word, Map dictionnary){
        return dictionnary.containsKey(word);
    }

    public static HashMap<String, List<String>> initializeDictionnary(File f){

        HashMap<String, List<String>> hm = new HashMap<String, List<String>>();

        try {

            BufferedReader bufferedReader = new BufferedReader(new FileReader(f));
            String mot = bufferedReader.readLine();

            while (mot != null) {
                // On ajoute le mot dans le prefixTree, on initialise sa valeur a null
                hm.put(mot, null);
                mot = bufferedReader.readLine();
            }

            bufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

        return hm;
    }

}
