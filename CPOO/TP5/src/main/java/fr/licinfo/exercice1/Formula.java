package fr.licinfo.exercice1;

/**
 * L'intérface <code>Formula</code> définit deux méthodes.
 * Permettant d'afficher la valeur ou l'expression d'une formule.
 */
public interface Formula {

    /**
     * Permet d'afficher une formule sous la forme d'une expression.
     *
     * @return chaîne de caractère d'une formule
     */
    String asString();

    /**
     * Permet d'afficher une formule sous la forme de sa valeur finale.
     *
     * @return la valeur de l'opération
     */
    Double asValue();

}
