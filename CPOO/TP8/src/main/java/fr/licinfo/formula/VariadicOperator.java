package fr.licinfo.formula;

import fr.licinfo.acyclique.FormulaVisitor;
import fr.licinfo.acyclique.ProductVisitor;

/**
 * Created by c16017548 on 27/09/16.
 */
public abstract class VariadicOperator implements Formula{

    @Override
    public String asString() {

        String str = "";
        Formula[] varTab = this.getVarTab();

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
        double dbl = this.initialValue();
        Formula[] varTab = this.getVarTab();

        for (Formula aVarTab : varTab) {
            dbl = cumulativeValue(dbl, aVarTab.asValue());
        }

        return dbl;
    }

    public abstract double initialValue();

    public abstract double cumulativeValue(double accumulator, double value);

    public abstract String symbol();

    public abstract Formula[] getVarTab();

}
