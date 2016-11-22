package fr.licinfo.acyclique;

import fr.licinfo.formula.*;

/**
 * Created by c16017548 on 08/11/16.
 */
public class XMLVisitor implements ProductVisitor<String>, SumVisitor<String>, VariableVisitor<String>, FormulaVisitor<String> {

    public String visit(Sum sum) {
        return visit(sum, "sum");
    }

    public String visit(Product product) {
        return visit(product, "product");
    }

    public String visit(Variable variable) {
        StringBuilder sb = new StringBuilder();
        sb.append("<var>").append(variable.asString()).append("</var>");

        return sb.toString();
    }

    private String visit(VariadicOperator operator, String tag){
        StringBuilder sb = new StringBuilder();

        sb.append("<").append(tag).append(">");

        Formula[] varTab = operator.getVarTab();

        for (int i = 0; i < varTab.length; i++){
            sb.append(varTab[i].accept(this));
        }

        sb.append("</").append(tag).append(">");

        return sb.toString();
    }
}
