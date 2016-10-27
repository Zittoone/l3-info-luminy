import javax.print.attribute.HashAttributeSet;
import java.io.*;
import java.net.URL;
import java.security.Key;
import java.util.List;

public class Main {

    public static void main(String[] args) {

        // ----- S U P P L E M E N T ----- //
        URL url = Main.class.getResource("dico2012.txt");

        final String filePath = url.getPath();

        PrefixTree<String> prefixTree = new PrefixTree<String>();

        File file = new File(filePath);

        // Ajout des mots dans PrefixTree
        try {

            BufferedReader bufferedReader = new BufferedReader(new FileReader(file));
            String mot = bufferedReader.readLine();

            while (mot != null) {
                System.out.println("Insertion de " + mot);
                // On ajoute le mot dans le prefixTree, et on ajoute le mot en tant que valeur.
                prefixTree.put(mot, mot);
                mot = bufferedReader.readLine();
            }

            bufferedReader.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        List<String> list = prefixTree.findAllCombinations("jourbon", true);
        // mettre le second argument à false pour ne pas utiliser au moins TOUTES les lettres.

        System.out.println("\nListe de mot possible pour la chaîne : \"jourbon\"\n" + list.toString());


        // Dans l'exemple ci-dessous, on obtient 2 résultat : [bonjour, bonjour]
        // car le mot "jourbon" comporte une lettre double : la lettre "o"
        // il y a donc 2 chemins possible pour atteindre le mot "bonjour" en utilisant les 2 "o"
        // différents. Un moyen de résoudre ce problème et de vérifier les doublons une fois le parcours complété.
        // Mais en soit ce n'est pas un problème, et cela montre en effet qu'il y a 2 manières de trouver "bonjour"
        // avec "jourbon".

    }
}
