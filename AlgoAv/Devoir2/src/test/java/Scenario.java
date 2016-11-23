import javafx.util.Pair;
import org.junit.Test;

import java.io.*;
import java.util.*;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.assertThat;

/**
 * Created by Alexis Couvreur on 17/11/2016.
 */
public class Scenario {

    public static void main(String[] args){


        // Etape 0
        // Création des instances
        File minidico = new File(Scenario.class.getResource("minidico.txt").getPath());
        //File fautes = new File(Scenario.class.getResource("fautes.txt").getPath());

        /**
         * On utilise un HashMap pour associer a chaque mot, leurs trigrammes
         */
        HashMap<String, List<String>> dictionnaire = buildList(minidico);

        // Le mot "balsamique" est dans le dictionnaire, mais pas "balamique" (suppression du 's')
        String motIncorrect = "balamique";

        // Etape 1
        // Vérification si le mot est contenu dans le dictionnaire
        if(dictionnaire.containsKey(motIncorrect)){
            // S'il est contenu dans le dictionnaire on arrête
            return;
        }

        // Etape 2
        // Construction de la liste des trigrammes
        List<String> trigrammesMot = Trigramme.obtenirTrigrammes(motIncorrect);
        // Je pense qu'il faut créer les trigrammes de chaque mots du dictionnaire à ce moment là aussi, car sinon ils sont créés pour rien

        // Etape 3
        // Pour chaque trigramme on récupère la liste des mots contenant ce trigramme
        Map<String, Integer> hm = new HashMap<>();
        for (String trigramme : trigrammesMot) {
            for (Map.Entry<String, List<String>> dicoEntry : dictionnaire.entrySet()){
                if(dicoEntry.getValue().contains(trigramme)){
                    if(hm.get(dicoEntry.getKey()) == null){
                        hm.put(dicoEntry.getKey(), 1);
                    } else {
                        hm.put(dicoEntry.getKey(), hm.get(dicoEntry.getKey()) + 1);
                    }
                }
            }
        }

        // Etape 4
        // on trie ces mots, et on garde ceux avec le plus de trigrammes en commun avec le mot à corriger(on peut en garder une centaine).
        hm = sortByValue(hm);

        //Etape 5
        // on calcule la distance d’édition de chacun avec le mot à corriger, on garde les meilleurs, triés dans
        // l’ordre de distance d’édition. Le premier est notre proposition, mais peut-être la bonne solution
        // n’est placée que 2e ou 3e, donc on donne une liste des meilleurs choix à l’utilisateur pour qu’il
        // choisisse celle qu’il préfère.
        List<Pair<String, Integer>> motPossibles = new ArrayList<>();
        for (String word : hm.keySet()) {

        }

        
    }

    public static HashMap<String, List<String>> buildList(File f){

        HashMap<String, List<String>> hm = new HashMap<String, List<String>>();

        try {

            BufferedReader bufferedReader = new BufferedReader(new FileReader(f));
            String mot = bufferedReader.readLine();

            while (mot != null) {
                // On ajoute le mot dans le prefixTree, et on ajoute le mot en tant que valeur.
                hm.put(mot, Trigramme.obtenirTrigrammes(mot));
                mot = bufferedReader.readLine();
            }

            bufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

        return hm;
    }

    private static Map<String, Integer> sortByValue(Map<String, Integer> unsortMap) {

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
        }

        return sortedMap;
    }

    public static <K, V> void printMap(Map<K, V> map) {
        for (Map.Entry<K, V> entry : map.entrySet()) {
            System.out.println("Key : " + entry.getKey()
                    + " Value : " + entry.getValue());
        }
    }
}
