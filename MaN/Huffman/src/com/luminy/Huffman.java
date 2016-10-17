package com.luminy;

import java.util.*;

/**
 * Created by Base on 18/09/2016.
 */
public class Huffman {

    public static HashMap<Character, Integer> getFrequencies(String texteClair) {
        HashMap<Character, Integer> map = new HashMap<>();

        for (int i = 0; i < texteClair.length(); i++) {
            char c = texteClair.charAt(i);
            Integer val = map.get(c);
            if (val != null) {
                map.put(c, val + 1);
            } else {
                map.put(c, 1);
            }
        }

        return map;
    }

    public static Arbre creerArbre(HashMap<Character, Integer> frequenciesMap) {

        ArrayList<Object> liste = new ArrayList<>();
        //Liste qui contiendra les noeuds et les valeurs pas encore placés dans l'arbre, les valeurs sont triées par ordre croissant
        //Retrouver la méthodologie ici : https://www.siggraph.org/education/materials/HyperGraph/video/mpeg/mpegfaq/huffman_tutorial.html

        Iterator it = frequenciesMap.entrySet().iterator();
        while (it.hasNext()) {
            HashMap.Entry pair = (HashMap.Entry) it.next();
            //System.out.println(pair.getKey() + " = " + pair.getValue()); //permet de voir chaques caractere different et son nombre d'occurences
            HashMap obj = new HashMap();
            obj.put(pair.getKey(), pair.getValue());
            liste.add(obj);
            it.remove();
        }

        //On a chaque loop au 2 valeurs les plus petites, quelles soient un noeud ou une valeur pas encore dans l'arbre
        for (int i = 0; i < liste.size(); i += 2) {
            Arbre a;

            if (liste.get(i) instanceof HashMap) { //Si c'est une valeur simple
                HashMap<Character, Integer> obj = (HashMap<Character, Integer>) liste.get(i);
                Map.Entry<Character, Integer> entry = obj.entrySet().iterator().next();

                a = new Arbre(entry.getValue(), null, null);
                a.setLetter(entry.getKey());

            } else { // c'est donc un noeud
                a = (Arbre) liste.get(i);

                if (i + 1 == liste.size()) {
                    return a;
                }
            }

            if (liste.get(i + 1) instanceof HashMap) {
                HashMap<Character, Integer> obj2 = (HashMap<Character, Integer>) liste.get(i + 1);
                Map.Entry<Character, Integer> entry2 = obj2.entrySet().iterator().next();

                Arbre feuille2 = new Arbre(entry2.getValue(), null, null);
                feuille2.setLetter(entry2.getKey());
                Arbre noeud = new Arbre(a.getVal() + feuille2.getVal(), a, feuille2);

                liste = insertValueInSortedArray(liste, noeud);
            } else {
                Arbre b = (Arbre) liste.get(i + 1);
                Arbre noeud = new Arbre(a.getVal() + b.getVal(), a, b);
                liste = insertValueInSortedArray(liste, noeud);
            }
        }

        Arbre lastNode = (Arbre) liste.get(liste.size() - 1);
        return lastNode;
    }

    public static ArrayList<Object> insertValueInSortedArray(ArrayList<Object> liste, Object obj) {
        ArrayList<Object> listeToReturn = liste;
        int weight = 0;
        if (obj instanceof HashMap) {
            HashMap<Character, Integer> a = (HashMap<Character, Integer>) obj;
            Map.Entry<Character, Integer> entry = a.entrySet().iterator().next();
            weight = entry.getValue();
        } else if (obj instanceof Arbre) {
            Arbre a = (Arbre) obj;
            weight = a.getVal();
        }

        int val;
        for (int i = 0; i < listeToReturn.size(); i++) {
            if (listeToReturn.get(i) instanceof HashMap) {
                HashMap<Character, Integer> a = (HashMap<Character, Integer>) listeToReturn.get(i);
                Map.Entry<Character, Integer> entry = a.entrySet().iterator().next();
                val = entry.getValue();
            } else {
                Arbre a = (Arbre) obj;
                val = a.getVal();
            }

            if (val > weight) {
                listeToReturn.add(i, obj);
                return listeToReturn;
            }

        }

        listeToReturn.add(obj);
        return listeToReturn;
    }

    public static HashMap<Character, Integer> sortByValue(HashMap<Character, Integer> map) {
        Set<Map.Entry<Character, Integer>> set = map.entrySet();
        List<Map.Entry<Character, Integer>> list = new ArrayList<Map.Entry<Character, Integer>>(set);

        Collections.sort(list, (o1, o2) -> (o1.getValue()).compareTo(o2.getValue()));

        LinkedHashMap<Character, Integer> sortedMap = new LinkedHashMap<>();
        for (Map.Entry<Character, Integer> entry : list) {
            sortedMap.put(entry.getKey(), entry.getValue());
        }

        return sortedMap;
    }

    // make a lookup table from symbols and their encodings
    private static void buildCode(String[] st, Arbre x, String s) {
        if (!x.isLeaf()) {
            buildCode(st, x.getFilsG(),  s + '0');
            buildCode(st, x.getFilsD(), s + '1');
        }
        else {
            st[x.getLetter()] = s;
        }
    }

    public static String encodeText(Arbre racine, String text){

        // The encoded text is composed of binary numbers (0-1)
        String decodedText = "";
        Arbre tArbre = racine;

        String[] st = new String[256];
        buildCode(st, racine, "");

        for (int i = 0; i < text.length(); i++) {
            String code = st[text.charAt(i)];
            for (int j = 0; j < code.length(); j++) {
                if (code.charAt(j) == '0') {
                    decodedText += '0';
                }
                else if (code.charAt(j) == '1') {
                    decodedText += '1';
                }
            }
        }


        return decodedText;
    }

    public static String decodeText(Arbre racine, String encodedText){

        // The encoded text is composed of binary numbers (0-1)
        String decodedText = "";
        Arbre tArbre = racine;

        for(int i = 0; i < encodedText.length(); i++){
            // Si c'est une feuille on arrête et on écrit
            if(tArbre.isLeaf()){
                decodedText += tArbre.getLetter();
                tArbre = racine;
            }
            if(encodedText.charAt(i) == '0'){
                tArbre = tArbre.getFilsG();
            } else {
                tArbre = tArbre.getFilsD();
            }
        }


        return decodedText;
    }

}
