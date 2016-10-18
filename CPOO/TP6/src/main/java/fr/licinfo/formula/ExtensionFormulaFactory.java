package fr.licinfo.formula;

import fr.licinfo.formula.strategy.Product;
import fr.licinfo.formula.strategy.Sum;
import fr.licinfo.formula.strategy.VariadicOperator;

/**
 * Created by sebastientosello on 18/10/2016.
 */
public class ExtensionFormulaFactory implements AbstractFormulaFactory {

    public Formula createConstant(Double value) {
        return new Constant(value);
    }

    public Formula createProduct(Formula... formulas){
        return new VariadicOperator(new Product(), formulas);
    }

    public Formula createSum(Formula... formulas){
        return new VariadicOperator(new Sum(), formulas);
    }
}
