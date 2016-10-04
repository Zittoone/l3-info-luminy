package fr.licinfo.formula;

/**
 * La classe <code>SquareRoot</code> implémente <code>Formula</code>.
 * Elle permet de rendre la valeur à la racine carrée donnée d'une <code>Formula</code>.
 */
public class SquareRoot implements Formula {

    /**
     * La <code>Formula</code> à rendre à la racine carrée
     */
    private Formula formula;

    /**
     * Constructeur prenant en paramètre une seule <code>Formula</code>
     * @param formula
     */
    public SquareRoot(Formula formula){
        this.formula = formula;
    }

    @Override
    public String asString() {
        return "sqrt(" + this.formula.asString() + ")";
    }

    @Override
    public Double asValue() {
        return Math.sqrt(this.formula.asValue());
    }
}