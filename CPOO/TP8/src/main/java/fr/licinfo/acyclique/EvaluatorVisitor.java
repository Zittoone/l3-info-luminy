package fr.licinfo.acyclique;

import fr.licinfo.formula.Product;
import fr.licinfo.formula.Sum;
import fr.licinfo.formula.Variable;

/**
 * Created by c16017548 on 08/11/16.
 */
public class EvaluatorVisitor<R extends Double> implements ProductVisitor<String>, SumVisitor<String>, VariableVisitor<String>, FormulaVisitor<String> {

    @Override
    public String visit(Sum sum) {
        return null;
    }

    @Override
    public String visit(Product product) {
        return null;
    }

    @Override
    public String visit(Variable variable) {
        return null;
    }
}
