import java.io.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by c16017548 on 09/11/16.
 */
public class Main {

    public static void main( String[] args )
    {
        // Création du prefix tree avec le dictionnaire
        System.out.println("--------------INSERCTION MINIDICO----------------");

        List<String> minidico = buildList("minidico.txt");

        List<String> fautes = buildList("fautes.txt");

        // Levenshtein
        Levenshtein lvsh = new Levenshtein(minidico);

        for (String mot: fautes) {
            long time;
            String motCorrect;

            time = System.nanoTime();
            motCorrect = lvsh.correctionDictionnaire(mot);
            time = (System.nanoTime() - time) / 1000;
            System.out.println(mot + " -> " + motCorrect + " (" + time + " microseconds)");
        }



    }

    public static List<String> buildList(String name){
        URL url = Main.class.getResource(name);

        final String filePath = url.getPath();

        List<String> list = new ArrayList<String>();

        File file = new File(filePath);

        // Ajout des mots dans PrefixTree
        try {

            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            String mot = bufferedReader.readLine();

            while (mot != null) {
                System.out.println("Insertion de " + mot);
                // On ajoute le mot dans le prefixTree, et on ajoute le mot en tant que valeur.
                list.add(mot);
                mot = bufferedReader.readLine();
            }

            bufferedReader.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return list;

    }
}
