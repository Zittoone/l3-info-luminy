package fr.licinfo.formula;

import fr.licinfo.acyclique.FormulaVisitor;
import fr.licinfo.acyclique.VariableVisitor;

/**
 * La classe <code>Variable</code> implémente <code>Formula</code>.
 * Elle permet d'assigner une valeur (double) à un nom (String).
 * Tel que : x (nom) = 1 (valeur).
 */
public class Variable implements Formula {

    /**
     * Le nom de la variable, celle qui sera affiché lors de l'appel de <code>asString()</code>
     */
    private String name;

    /**
     * La valeur de la variable, permettant d'effectué le calcul
     * lors de l'appel de <code>asValue()</code>
     */
    private double value;

    /**
     * Initialise une pair nom - valeur
     * @param x le nom de la variable
     * @param v la valeur de la variable
     */
    public Variable(String x, double v) {
        this.name = x;
        this.value = v;
    }

    /**
     * Permet de modifier la valeur de la variable sans changer le nom.
     * @param val la nouvelle valeur
     */
    public void set(double val) {
        this.value = val;
    }

    @Override
    public String asString() {
        return this.name;
    }

    @Override
    public Double asValue() {
        return this.value;
    }

    @Override
    public <R> R accept(FormulaVisitor<R> formulaVisitor) {
        return (R) ((VariableVisitor)formulaVisitor).visit(this);
    }
}
