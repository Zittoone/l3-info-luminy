import java.io.File;
import java.util.List;

/**
 * Created by Alexis Couvreur on 17/11/2016.
 */
public class Scenario {

    public static void main(String[] args){


        // Etape 0
        // Création des instances
        File minidico = new File(Scenario.class.getResource("minidico.txt").getPath());
        //File fautes = new File(Scenario.class.getResource("fautes.txt").getPath());

        // Le mot "balsamique" est dans le dictionnaire, mais pas "balamique" (suppression du 's')
        String motIncorrect = "balamique";

        List<String> propositions = Trigramme.executeProcess(motIncorrect, minidico);

        System.out.println(motIncorrect + " -> " + propositions);
        
    }
}
