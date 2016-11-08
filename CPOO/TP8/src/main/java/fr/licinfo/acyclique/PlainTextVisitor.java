package fr.licinfo.acyclique;

import fr.licinfo.formula.*;

/**
 * Created by c16017548 on 08/11/16.
 */
public class PlainTextVisitor implements ProductVisitor<String>, SumVisitor<String>, VariableVisitor<String>, FormulaVisitor<String>{

    public String visit(Sum sum) {
        return visit(sum, sum.symbol());
    }

    public String visit(Product product) {
        return visit(product, product.symbol());
    }

    public String visit(Variable variable) {
        return variable.asString();
    }

    private String visit(VariadicOperator operator, String tag){
        StringBuilder sb = new StringBuilder();

        sb.append("(");

        Formula[] varTab = operator.getVarTab();

        for (int i = 0; i < varTab.length; i++){
            sb.append(varTab[i].asString());

            if (i != varTab.length - 1){
                sb.append(tag);
            }

        }

        sb.append(")");

        return sb.toString();
    }
}
