package fr.licinfo.acyclique;

import fr.licinfo.formula.Product;
import fr.licinfo.formula.Sum;
import fr.licinfo.formula.Variable;
import fr.licinfo.formula.VariadicOperator;

/**
 * Created by c16017548 on 08/11/16.
 */
public class XMLVisitor implements ProductVisitor<String>, SumVisitor<String>, VariableVisitor<String>, FormulaVisitor<String> {

    public String visit(Sum sum) {
        return null;
    }

    public String visit(Product product) {
        return null;
    }

    public String visit(Variable variable) {
        return null;
    }

    private String visit(VariadicOperator operator, String tag){
        return null;
    }
}
