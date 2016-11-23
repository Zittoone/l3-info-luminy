package fr.licinfo.acyclique;

import fr.licinfo.formula.*;

/**
 * Created by c16017548 on 08/11/16.
 */
public class EvaluatorVisitor<R extends Double> implements ProductVisitor<R>, SumVisitor<R>, VariableVisitor<R>, FormulaVisitor<R> {

    @Override
    public R visit(Sum sum) {
        return visit(sum, sum.symbol());
    }

    @Override
    public R visit(Product product) {
        return visit(product, product.symbol());
    }

    @Override
    public R visit(Variable variable) {
        return (R) variable.asValue();
    }

    private R visit(VariadicOperator operator, String tag) {
        Double res = operator.initialValue();

        Formula[] varTab = operator.getVarTab();

        for (int i = 0; i < varTab.length; i++) {
            res += (Double) varTab[i].accept(this);
        }

        return (R) res;
    }
}
