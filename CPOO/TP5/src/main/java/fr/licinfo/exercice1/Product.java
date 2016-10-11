package fr.licinfo.exercice1;

/**
 * La classe <code>Product</code> implémente <code>Formula</code>.
 * Elle permet de faire le produit entre 1 à n double.
 */
public class Product implements Operator {

    /**
     * Le tableau de valeur
     */
    private Formula[] varTab;

    /**
     * Le constructeur prenant un nombre indéfinit de paramètre.
     * @param tab
     */
    public Product(Formula... tab){
        this.varTab = tab;
    }

    public String symbol(){
        return " * ";
    }

    public double initialValue(){
        return 1;
    }

    public double cumulativeValue(double accumulator, double value){
        return accumulator * value;
    }

    public Formula[] getVarTab(){
        return varTab;
    }
}
