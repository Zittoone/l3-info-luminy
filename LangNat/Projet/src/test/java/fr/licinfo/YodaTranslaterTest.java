package fr.licinfo;

import org.junit.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;

/**
 * Created by Alexis Couvreur on 23/04/2017.
 */
public class YodaTranslaterTest {

    private YodaTranslater translater = new YodaTranslater();

    @Test
    public void testSV() {
        String sentence1 = "Les garçons ont sauté au-dessus du mur.";
        String sentence2 = "Il dort pendant les cours.";
        String sentence3 = "Les oiseaux de la même plume volent ensemble.";
        assertThat(translater.translate(sentence1), equalToIgnoringCase("Au-dessus du mur, les garçons ont sauté."));
        assertThat(translater.translate(sentence2), equalToIgnoringCase("Pendant les cours, il dort."));
        assertThat(translater.translate(sentence3), equalToIgnoringCase("Ensemble, les oiseaux de la même plume volent."));
    }

    @Test
    public void testSVO() {
        String sentence1 = "Elle enseigne l'Anglais à l'université.";
        String sentence2 = "Sa voiture a percutée un arbre ce matin.";
        String sentence3 = "Ils vont rencontrer le patron Lundi prochain.";
        assertThat(translater.translate(sentence1), equalToIgnoringCase("À l'université, elle enseigne l'anglais."));
        assertThat(translater.translate(sentence2), equalToIgnoringCase("Un arbre ce matin, sa voiture a percutée."));
        assertThat(translater.translate(sentence3), equalToIgnoringCase("Rencontrer le patron Lundi prochain, ils vont."));
    }

    @Test
    public void testSVIODO(){
        String sentence1 = "La femme a donnée à sa fille un cadeau pour son anniversaire.";
        String sentence2 = "Le gestionnaire de la banque a accordé un prêt pour le pauvre agriculteur ce matin.";
        String sentence3 = "M. Mendoza nous a appris le grec à l'époque.";
        assertThat(translater.translate(sentence1), equalToIgnoringCase("À sa fille un cadeau pour son anniversaire, la femme a donnée."));
        assertThat(translater.translate(sentence2), equalToIgnoringCase("Un prêt pour le pauvre agriculteur ce matin, le gestionnaire de la banque a accordé."));
        assertThat(translater.translate(sentence3), equalToIgnoringCase("Le grec à l'époque, M. Mendoza nous a appris."));
    }

    @Test
    public void testSVSC(){
        String sentence1 = "Hannah était un professeur à Delhi.";
        String sentence2 = "Le vieux monsieur a l'air heureux aujourd'hui.";
        String sentence3 = "Ces jeunes gens vont devenir des experts bientôt.";
        assertThat(translater.translate(sentence1), equalToIgnoringCase("Un professeur à delhi, hannah était."));
        assertThat(translater.translate(sentence2), equalToIgnoringCase("l'air heureux aujourd'hui, Le vieux monsieur a."));
        assertThat(translater.translate(sentence3), equalToIgnoringCase("devenir des experts bientôt, Ces jeunes gens vont."));
    }

    @Test
    public void testSVOOC(){
        String sentence1 = "Le Premier ministre a nommé M. X un ministre en 2004.";
        String sentence2 = "L'inspecteur a trouvé l'homme innocent.";
        String sentence3 = "Le locateur a appelé le nouveau locataire un escroc.";
        assertThat(translater.translate(sentence1), equalToIgnoringCase("M. x un ministre en 2004, le premier ministre a nommé."));
        assertThat(translater.translate(sentence2), equalToIgnoringCase("l'homme innocent, L'inspecteur a trouvé."));
        assertThat(translater.translate(sentence3), equalToIgnoringCase("le nouveau locataire un escroc, Le locateur a appelé."));
    }

}
