package fr.licinfo.formula;

/**
 * La classe <code>Sum</code> implémente <code>Formula</code>.
 * Elle permet de faire la somme entre 1 à n double.
 */
public class Sum extends VariadicOperator {

    /**
     * Le tableau de valeur
     */
    private Formula[] varTab;

    /**
     * Constructeur prenant en compte un nombre non définit de paramètre.
     *
     * @param f1
     */
    public Sum(Formula... f1){
        this.varTab = f1;
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
        double dbl = 0.0;

        for (Formula aVarTab : varTab) {
            dbl += aVarTab.asValue();
        }

        return dbl;
    }
    */

    public String symbol(){
        return " + ";
    }

    public double initialValue(){
        return 0;
    }

    public double cumulativeValue(double accumulator, double value){
        return accumulator + value;
    }

    public Formula[] getVarTab(){
        return varTab;
    }
}
