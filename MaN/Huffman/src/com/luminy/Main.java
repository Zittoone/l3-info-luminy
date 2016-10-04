package com.luminy;

import java.io.*;
import java.util.HashMap;

public class Main {

    public static void main(String[] args) {

        // On ouvre les fichiers
        File clair = new File("C:\\Users\\zT00N\\IdeaProjects\\Huffman\\res\\", "clair.txt");
        File encode = new File("C:\\Users\\zT00N\\IdeaProjects\\Huffman\\res\\", "encode.txt");

        String texteClair = fileTextToString(clair);
        HashMap<Character, Integer> frequenciesMap;


        // On récupere un hashmap contenant les frequences d'apparation pour chaque caracteres.
        frequenciesMap = Huffman.getFrequencies(texteClair);
        frequenciesMap = Huffman.sortByValue(frequenciesMap);

        Arbre keyTree = Huffman.creerArbre(frequenciesMap);
        keyTree.afficher(keyTree);

        String encodedText = Huffman.encodeText(keyTree, texteClair);
        System.out.println("\n" + encodedText);
        String decodedText = Huffman.decodeText(keyTree, encodedText);
        System.out.println(decodedText);
        writeInFile(encode, Huffman.encodeText(keyTree, texteClair));




        //System.out.println("Texte d'origine : \n" + texteClair);
        //System.out.println("Texte encodé : \n" + texteEncode);



    }

    private static String fileTextToString(File f){

        String text = "";

        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
            try {
                StringBuilder sb = new StringBuilder();
                String line = br.readLine();

                while (line != null) {
                    sb.append(line);
                    sb.append(System.lineSeparator());
                    line = br.readLine();
                }
                text = sb.toString();
            } finally {
                br.close();
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return text;
    }

    private static void writeInFile(File f, String text){

        PrintWriter writer = null;
        try {
            writer = new PrintWriter(f);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        writer.print(text);
        writer.close();
    }

}
