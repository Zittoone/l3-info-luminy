package fr.licinfo.formula;

/**
 * La classe <code>AbsoluteValue</code> implémente <code>Formula</code>.
 * Elle permet de rendre la valeur absolue d'une <code>Formula</code>.
 */
public class AbsoluteValue implements Formula {

    /**
     * La formule dont on doit calculer la valeur absolue
     */
    private Formula formula;

    /**
     * On calcul la valeur absolue d'une seule formule.
     * @param formula
     */
    public AbsoluteValue(Formula formula) {
        this.formula = formula;
    }

    @Override
    public String asString() {

        return "|" + formula.asString() + "|";
    }

    @Override
    public Double asValue() {
        return Math.abs(formula.asValue());
    }
}
