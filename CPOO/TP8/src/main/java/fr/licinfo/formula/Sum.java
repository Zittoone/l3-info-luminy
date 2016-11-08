package fr.licinfo.formula;


import fr.licinfo.acyclique.FormulaVisitor;
import fr.licinfo.acyclique.SumVisitor;

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

    public String symbol(){
        return "+";
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

    @Override
    public <R> R accept(FormulaVisitor<R> formulaVisitor) {
        return (R) ((SumVisitor)formulaVisitor).visit(this);
    }
}
