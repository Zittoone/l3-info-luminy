package fr.licinfo.formula;

/**
 * La classe <code>Product</code> implémente <code>Formula</code>.
 * Elle permet de faire le produit entre 1 à n double.
 */
public class Product extends VariadicOperator implements Formula {

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

    /*
    @Override
    public String asString() {

        String str = "";

        for (int i = 0; i < varTab.length; i++){
            str += varTab[i].asString();

            if (i != varTab.length - 1){
                str += this.symbol();
            }

        }

        return "(" + str + ")";
    }

    @Override
    public Double asValue() {
        double dbl = 1.0;

        for (Formula aVarTab : varTab) {
            dbl *= aVarTab.asValue();
        }

        return dbl;
    }
    */

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
