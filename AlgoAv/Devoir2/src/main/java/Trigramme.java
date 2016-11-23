import java.util.ArrayList;
import java.util.List;

/**
 * Created by Alexis Couvreur on 16/11/2016.
 */
public final class Trigramme {

    private Trigramme(){}

    public static List<String> obtenirTrigrammes(String mot){

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

}
