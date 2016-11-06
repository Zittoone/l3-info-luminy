package fr.licinfo.formula;

/**
 * Created by sebastientosello on 18/10/2016.
 */
public interface AbstractFormulaFactory {
    public Formula createConstant(Double value);

    public Formula createProduct(Formula... formulas);

    public Formula createSum(Formula... formulas);
}
