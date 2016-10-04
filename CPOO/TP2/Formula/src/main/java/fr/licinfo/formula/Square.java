package fr.licinfo.formula;

/**
 * La classe <code>Square</code> implémente <code>Formula</code>.
 * Elle permet de rendre la valeur à la au carré d'une <code>Formula</code>.
 */
public class Square implements Formula {

    /**
     * La <code>Formula</code> à rendre au carré
     */
    private Formula formula;

    /**
     * Constructeur prenant en compte une seule <code>Formula</code>
     * @param value
     */
    public Square(Formula value){
        this.formula = value;
    }

    @Override
    public String asString() {
        return this.formula.asString() + "^2";
    }

    @Override
    public Double asValue() {
        return this.formula.asValue() * this.formula.asValue();
    }
}
