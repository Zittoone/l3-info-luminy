package fr.licinfo;

/**
 * Created by Alexis Couvreur on 21/09/2016.
 *
 * La classe <code>Stack</code> implémente la classe <code>Vector</code>
 * Les éléments peuvent être ajouté ou retiré tel une pile.
 * On peut seulement retirer l'élément au sommet, ou en ajouter un au dessus.
 */
public class Stack {

    private Vector<Integer> pile;

    /**
     * Permet de créer une pile avec comme taille de départ <code>initialCapacity</code>
     * @param initialCapacity
     */
    public Stack(int initialCapacity){
        pile = new Vector(initialCapacity);
    }

    public Stack(){
        this(10);
    }

    /**
     * Permet d'ajouter une valeur au somment de la pile.
     *
     * @param value
     * @return l'objet ajouté
     */
    public int push(int value){
        pile.add(value);
        return pile.get(pile.size());
    }

    /**
     * Permet de retirer la valeur au sommet de la pile
     * @return l'objet retiré
     */
    public int pop(){
        int topStack = pile.get(pile.size());
        pile.resize(pile.size() - 1);
        return topStack;
    }

    /**
     * Retourne l'objet au sommet de la pile
     *
     * @return
     */
    public int peek(){
        return pile.get(pile.size());
    }

    /**
     * Vérifie si la pile est vide
     * @return vrai si la pile est vide
     *         faux sinon
     */
    public boolean empty(){
        return pile.isEmpty();
    }

}
