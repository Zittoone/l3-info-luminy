package com.luminy;

import java.io.*;

public class Main {

    public static void main(String[] args) {

        MainFrame mf = new MainFrame();

        // On ouvre les fichiers
        File clair = new File("C:\\Users\\zT00N\\IdeaProjects\\Vigenere\\res", "clair.txt");
        File encode = new File("C:\\Users\\zT00N\\IdeaProjects\\Vigenere\\res", "encode.txt");
        //File dictionnaire = new File("C:\\Users\\zT00N\\IdeaProjects\\Vigenere\\res", "dictionnaire.txt");
/*
        //Vigenere vig = new Vigenere(dictionnaire);
        String texteClair = fileTextToString(clair);
        String texteEncode = "";
        String key = "";

        // On lit la clés
        try {
            System.out.println("Entrer la clé de cryptage :");
            key = new BufferedReader(new InputStreamReader(System.in)).readLine();
        } catch (IOException e) {
            e.printStackTrace();
        }
/*
        // On encode le texte et on écrit dans le fichier
        texteEncode = vig.encode(texteClair, key);
        writeInFile(encode, texteEncode);



        System.out.println("Texte d'origine : \n" + texteClair);
        System.out.println("Texte encodé : \n" + texteEncode);

        System.out.println("\nDéduction de la taille du motif en cours ...");
        String decode = vig.decode(texteEncode);

        System.out.println("\nLe motif d'encodage du texte a une longueur de " + decode);
*/
    }

    public static String fileTextToString(File f){

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

    public static void writeInFile(File f, String text){

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
