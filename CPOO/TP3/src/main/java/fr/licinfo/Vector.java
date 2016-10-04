package fr.licinfo;

/**
 * Created by c16017548 on 20/09/16.
 */

import java.util.Arrays;

/**
 * La classe <code>Vector</code> implémente un tableau d'entiers
 * de taille dynamique. Les éléments du vecteur sont stockés dans un tableau.
 * La taille de ce tableau est au minimum doublée à chaque fois qu'il est
 * nécessaire de le faire grossir.
 */
public class Vector<T> {

    /**
     * Tableau permettant de stocker les éléments du vecteur.
     * Seuls les <code>size</code> premiers éléments font partie du vecteur.
     * La taille de ce tableau est égale à la capacité du vecteur, c'est-à-dire,
     * au nombre d'éléments maximum que le vecteur peut contenir sans
     * avoir besoin d'allouer un nouveau tableau.
     */
    private Object[] elements;

    /**
     * Nombre d'éléments présents dans le vecteur.
     */
    private int size;

    /**
     * Construit un vecteur de capacité initiale <code>initialCapacity</code>.
     *
     * @param initialCapacity Capacité initiale du vecteur
     */
    public Vector(int initialCapacity) {
        elements = new Object[initialCapacity];
        size = 0;
    }

    public Vector() {
        this(10);
    }

    /**
     * Augmente la capacité du vecteur si nécessaire de façon
     * à permettre le stockage d'au moins <code>minCapacity</code>
     * éléments. S'il est nécessaire d'augmenter la capacité du vecteur,
     * elle est au minimum doublée.
     *
     * @param minCapacity Capacité minimale à assurer
     */
    public void ensureCapacity(int minCapacity) {
        int oldCapacity = elements.length;
        if (minCapacity > oldCapacity) {
            int newCapacity = oldCapacity * 2;
            if (newCapacity < minCapacity)
                newCapacity = minCapacity;
            //noinspection Since15
            elements = Arrays.copyOf(elements, newCapacity);
        }
    }

    /**
     *
     * @param newSize la nouvelle taille du nombre vraiment présent dans le tableau
     *                si newSize est inférieur à 0, newSize vaut 0.
     * @throws ArrayIndexOutOfBoundsException si la nouvelle taille est strictement inférieur à 0
     */

    public void resize(int newSize) {
        if(newSize < 0)
            throw new IndexOutOfBoundsException("New size "+newSize+" cannot be negative.");
        ensureCapacity(newSize);
        for(int i = newSize; i < capacity(); i++)
            elements[i] = 0;
        this.size = newSize;
    }

    /**
     * Retourne la capacité du vecteur.
     *
     * @return Capacité du vecteur.
     */
    public int capacity() {
        return elements.length;
    }

    /**
     * Retourne le nombre d'élément dans le tableau
     *
     * @return Nombre d'élément présent dans le tableau
     */
    public int size() { return size; }

    /**
     * Retourne vrai si le tableau est vide
     * Retourne faux sinon
     *
     * @return true si le tableau est vide, faux sinon
     */
    public boolean isEmpty() { return size == 0; }

    /**
     * Procédure ajoutant un élément au tableau
     * Augmentant la taille du tableau
     *
     * @param element l'élément à ajouter
     */
    public void add(int element) {
        this.elements[this.size] = element;
        this.resize(this.size + 1);
    }

    /**
     * Procédure qui permet de changer la valeur du tableau a un indice donné.
     * Une exception est renvoyée si l'index est incorrect.
     *
     * @param index Index de l'élément, strictement inférieur ou égal à size et supérieur à 0
     * @param element la valeur par laquelle on remplace l'élément
     * @throws ArrayIndexOutOfBoundsException si l'index est inférieur à zero ou supérieur à size
     */
    public void set(int index, int element) throws ArrayIndexOutOfBoundsException {
        if(index > size || index < 0)
            throw new ArrayIndexOutOfBoundsException("Index "+index+" is out of range [0, "+(size-1)+"].");
        this.elements[index] = element;
    }

    /**
     * Retourne la valeur du tableau à la position voulu.
     * Une exception est renvoyée si l'index est incorrect.
     *
     * @param index la position de l'élément, strictement inférieur ou égal à size et supérieur à 0
     * @return l'élément du tableau à l'index donné
     * @throws ArrayIndexOutOfBoundsException si l'index est inférieur à zero ou supérieur à size
     */
    public T get(int index) {
        if(index > size || index < 0)
            throw new ArrayIndexOutOfBoundsException("Index "+index+" is out of range [0, "+(size-1)+"].");
        return (T) elements[index];
    }

}