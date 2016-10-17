package com.luminy;

import java.io.*;
import java.text.Normalizer;
import java.util.ArrayList;
import java.util.HashMap;

import static com.luminy.ASCII.*;

/**
 * Created by zT00N on 15/09/2016.
 */
public class Vigenere {

    private HashMap<String, Float> dictionnaireOcc = new HashMap<String, Float>();

    public Vigenere(File f){

        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
            try {
                StringBuilder sb = new StringBuilder();
                String line = br.readLine();

                while (line != null) {

                    String character = line.split(":")[0];
                    Float percent = Float.parseFloat(line.split(":")[1]);

                    dictionnaireOcc.put(character, percent);
                    sb.append(line);
                    sb.append(System.lineSeparator());
                    line = br.readLine();
                }
            } finally {
                br.close();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String encode(String text, String key) {

        String validKey = key;
        // On applique une expression régulière a la clé passé en paramètre pour sa validité
        // Supprime toute les ponctuations et met en majuscule
        text = Normalizer.normalize(text, Normalizer.Form.NFD)
                .replaceAll("\\p{InCombiningDiacriticalMarks}+", "");
        validKey = Normalizer.normalize(validKey, Normalizer.Form.NFD)
                .replaceAll("\\p{InCombiningDiacriticalMarks}+", "");


        validKey = validKey.replaceAll("[^A-Za-z]+", "").toUpperCase();
        text = text.replaceAll("[^A-Za-z]+", "").toUpperCase();

        // Tableau de caractère afin de manipuler un à un les caractères
        char encodedText[] = new char[text.length()];

        for (int i = 0; i < text.length(); i++) {

            // On récupère la clé courrante
            char cKey = validKey.charAt(i % validKey.length());

            // On récupère le caractère à coder courrant
            char cChar = text.charAt(i);

            // On encode le caractère via l'ajout des codes ASCII des deux caractères puis en effectuant une remise à l'échelle
            char encodedChar = toChar((((toASCII(cKey) + toASCII(cChar)) - 130) % 26) + 65);

            // On rend le caractère encoder à sa place dans le tableau de caractère
            encodedText[i] = encodedChar;
        }

        return new String(encodedText);
    }

    private int valeurMajoritaire(ArrayList<Integer> a) {
        int qMax = 0; //Quantity of times the maximum repeating number appears
        int temp, compare, max = 0; //temp: stores the quantity of times the compared
        //number repeats itself
        //
        //compare: number to be compared
        //
        //max: number that repeats the most times in the
        //array

        for (int i = 0; i < a.size(); i++) {
            temp = 0;
            compare = a.get(i);

            for (Integer anA : a)
                if (anA == compare) {
                    temp++;
                }

            if (temp > qMax) {
                max = compare;
                qMax = temp;
            }
        }

        return max;
    }

    private boolean is_prime(int num) {
        if (num <= 1) return false;
        if (num % 2 == 0 && num > 2) return false;
        for (int i = 3; i < num / 2; i += 2) {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    private int pgcd(int a, int b) {
        int r;
        while (b != 0) {
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    private int vigenereLongueur(String text) {

        int indexMotif;
        int pMotif;
        char motif[] = new char[text.length()];
        ArrayList<Pair> liste = new ArrayList<Pair>();

        if(text.length() > 1000){
            pMotif = 3;
        } else if(text.length() > 300){
            pMotif = 2;
        } else pMotif = 1;

        for (int i = 0; i < text.length() - 1; i++) {
            for (int j = i + 1; j < text.length(); j++) {
                indexMotif = 0;
                int i2 = i;
                int j2 = j;

                while (j2 < text.length() && text.charAt(i2) == text.charAt(j2)) {

                    motif[indexMotif++] = text.charAt(i2);
                    i2++;
                    j2++;
                }

                if (indexMotif > pMotif) {
                    i = i2;
                    Pair t_pair = new Pair(new String(motif), i, j - i2 + indexMotif);

                    liste.add(t_pair);
                    break;

                }
            }
        }

        ArrayList<Integer> distance_tab = new ArrayList<Integer>();
        for (Pair aListe : liste) {
            if (!is_prime(aListe.getDistancePair())) {
                distance_tab.add(aListe.getDistancePair());
            }
        }

        ArrayList<Integer> pgcdTab = new ArrayList<Integer>();
        for (int i = 0; i < liste.size(); i++) {
            for (int j = i + 1; j < liste.size(); j++) {
                pgcdTab.add(pgcd(liste.get(i).getDistancePair(), liste.get(j).getDistancePair()));
            }
        }

        return valeurMajoritaire(pgcdTab);
    }

    public String decodeKey(String text) {

        return trouverCle(text, vigenereLongueur(text));
    }

    private String trouverCle(String text, int longueurCle) {
        char cle[] = new char[longueurCle];
        int[] nbCar;
        int valeurMax;
        int indexValeurMax;
        int index;
        int codeAsciiLettre;
        int carEAscii;
        for(int i = 0 ; i < longueurCle ; i++)
        {
            index = i;
            // Tableau de l'alphabet crypté avec la pondération
            nbCar = new int[26];
            valeurMax = -1;
            indexValeurMax = -1;
            while(index < text.length()) {
                codeAsciiLettre = (int) text.charAt(index);
                nbCar[codeAsciiLettre - 65]++;
                index += longueurCle;
            }
            for(int j = 0 ; j < 26 ; j++) {
                if(nbCar[j] > valeurMax) {
                    valeurMax = nbCar[j];
                    indexValeurMax = j;
                }
            }
            carEAscii = indexValeurMax + 65;
            if(carEAscii < 69) {
                cle[i] = toChar(90 - (69 - carEAscii) + 1);
            }
            else {
                cle[i] = toChar(65 + (carEAscii - 69));
            }
        }
        return new String(cle);
    }

    public String decodeText(String text, String key){

        // Tableau de caractère afin de manipuler un à un les caractères
        char decodedText[] = new char[text.length()];

        for (int i = 0; i < text.length(); i++) {

            // On récupère la clé courrante
            char cKey;
            try {
                cKey = key.charAt(i % key.length());
            } catch (ArithmeticException e){
                return "Impossible de trouver la clé, texte trop court (" + text.length() + " caractères).";
            }


            // On récupère le caractère à coder courrant
            char cChar = text.charAt(i);

            // On rend le caractère encoder à sa place dans le tableau de caractère
            if(ASCII.toASCII(cChar) >= ASCII.toASCII(cKey)) {
                decodedText[i] = ASCII.toChar(ASCII.toASCII(cChar) - ASCII.toASCII(cKey) + 65);
            }
            else {
                decodedText[i] = ASCII.toChar(ASCII.toASCII(cChar) + 26 - ASCII.toASCII(cKey) + 65);
            }

        }

        return new String(decodedText);

    }




}
