import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by Alexis Couvreur on 17/11/2016.
 */
public class Scenario {

    public static void main(String[] args) {
        // Utilisation du dico2012.txt
        File dico2012 = new File(Scenario.class.getResource("dico2012.txt").getPath());

        Trigramme trig = new Trigramme();
        trig.initializeDictionnary(dico2012);

        executeScenario("balamique", trig);

        System.out.println("\n\nAppuyez sur <Enter> pour éxecuter le supplément ...");
        try {
            System.in.read();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // ---------------- SUPPLEMENT ---------------- //

        // Nous allons tester pour chaque mot dans "fautes.txt" si la proposition numéro 1 est égale à sa correction dans "minidico.txt"
        List<String> fautes = initializeWordList(new File(Scenario.class.getResource("fautes.txt").getPath()));
        List<String> correct = initializeWordList(new File(Scenario.class.getResource("minidico.txt").getPath()));
        List<String> correctionNotFound = new ArrayList<>();

        long debutBoucle = System.currentTimeMillis();
        int nbMotCorrige = 0;

        for (int i = 0; i < fautes.size(); i++) {
            if (executeScenario(fautes.get(i), trig).contains(correct.get(i))){
                nbMotCorrige++;
            } else correctionNotFound.add(fautes.get(i));
        }

        System.out.println("\n\nTemps total pour corriger chaque mot de \"fautes.txt\" : " + (System.currentTimeMillis() - debutBoucle) + " ms.");
        System.out.println("Avec un taux de réussite de " + (nbMotCorrige*100) / correct.size() + "%. (" + nbMotCorrige + "/" + correct.size() + ")");
        System.out.println("\n\nVoici les mots dont la correction n'a pas été trouvée : \n" + correctionNotFound.toString());


    }

    public static List<String> executeScenario(String word, Trigramme trig) {
        System.out.println("-- Début du scénario --");

        List<String> propositions = trig.executeProcess(word);

        System.out.println("\n\nVoici les propositions pour la correction du mot \"" + word + "\" triées dans l'ordre du plus probable au moins :");
        for (int i = 0; i < propositions.size(); i++) {
            System.out.println((i + 1) + ". " + propositions.get(i));
        }

        System.out.println("-- Fin du scénario --");
        return propositions;
    }

    public static List<String> initializeWordList(File f) {

        List<String> list = new ArrayList<>();
        System.out.println("Initialisation du dictionnaire, traitement du fichier \"" + f.getName() + "\"");
        long debut = System.currentTimeMillis();
        try {

            BufferedReader bufferedReader = new BufferedReader(new FileReader(f));
            String mot = bufferedReader.readLine();

            while (mot != null) {
                list.add(mot);
                mot = bufferedReader.readLine();
            }

            bufferedReader.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Dictionnaire initialisé. (" + (System.currentTimeMillis() - debut) + " ms)");
        return list;
    }

}
