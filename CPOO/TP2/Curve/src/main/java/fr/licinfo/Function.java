package fr.licinfo;

import fr.licinfo.formula.Formula;
import fr.licinfo.formula.Variable;

/**
 * Created by c16017548 on 27/09/16.
 */
public class Function {

    /**
     * Function est de la forme ax + b
     * où formula est ac et variable b.
     */
    private Formula formula;

    public Variable getVariable() {
        return variable;
    }

    private Variable variable;

    public Function(Formula formula, Variable variable){
        this.formula = formula;
        this.variable = variable;
    }

    public double process(){

        return this.formula.asValue();
    }


}
