package com.luminy;

/**
 * Created by zT00N on 15/09/2016.
 */
public class Pair {

    // La chaîne qui forme une paire
    private String chaine;

    // L'index de début du motif dans la chaîne
    private int indexDebutMotif;

    // La distance du initiale jusqu'a sa paire
    private int distancePair;

    public Pair(String chaine, int indexDebutMotif, int distancePair) {
        this.chaine = chaine;
        this.indexDebutMotif = indexDebutMotif;
        this.distancePair = distancePair;
    }

    public String getChaine() {
        return chaine;
    }

    public void setChaine(String chaine) {
        this.chaine = chaine;
    }

    public int getIndexDebutMotif() {
        return indexDebutMotif;
    }

    public void setIndexDebutMotif(int indexDebutMotif) {
        this.indexDebutMotif = indexDebutMotif;
    }

    public int getDistancePair() {
        return distancePair;
    }

    public void setDistancePair(int distancePair) {
        this.distancePair = distancePair;
    }


}
