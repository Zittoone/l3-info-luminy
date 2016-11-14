package fr.licinfo.cyclique;

import fr.licinfo.formula.Product;
import fr.licinfo.formula.Sum;
import fr.licinfo.formula.Variable;
import fr.licinfo.formula.VariadicOperator;

/**
 * Created by c16017548 on 08/11/16.
 */
public class EvaluatorVisitor<R extends Double> implements FormulaVisitor<R> {

    @Override
    public R visit(Variable variable) {
        return null;
    }

    @Override
    public R visit(Sum sum) {
        return null;
    }

    @Override
    public R visit(Product product) {
        return null;
    }

    private R visit(VariadicOperator operator, String tag){
        return null;
    }
}
