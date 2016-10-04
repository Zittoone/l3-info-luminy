package fr.licinfo.formula;

/**
 * La classe <code>Power</code> implémente <code>Formula</code>.
 * Elle permet de rendre la valeur d'une formule à la puissance donnée.
 */
public class Power implements Formula {

    /**
     * La formule à laqielle on applique la puissance
     */
    private Formula formula;

    /**
     * La valeur de la puissance à appliquer
     */
    private double power;

    /**
     * Constructeur de <code>Power</code>
     * @param value
     * @param power
     */
    public Power(Formula value, double power){
        this.formula = value;
        this.power = power;
    }

    @Override
    public String asString() {
        return formula.asString() + "^" + this.power;
    }

    @Override
    public Double asValue() {
        return Math.pow(formula.asValue(), this.power);
    }
}
