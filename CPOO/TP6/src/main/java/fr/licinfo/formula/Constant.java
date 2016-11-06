package fr.licinfo.formula;

import fr.licinfo.formula.Formula;

/**
 * Created by sebastientosello on 18/10/2016.
 */
public class Constant implements Formula {

    private final double value;

    public Constant(double v){
        this.value = v;
    }

    @Override
    public String asString() {
        return String.format("%.6f", value);
    }

    @Override
    public Double asValue() {
        return value;
    }
}
