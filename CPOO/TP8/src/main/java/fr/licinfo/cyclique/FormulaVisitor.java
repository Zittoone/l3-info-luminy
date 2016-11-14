package fr.licinfo.cyclique;

import fr.licinfo.formula.Product;
import fr.licinfo.formula.Sum;
import fr.licinfo.formula.Variable;

/**
 * Created by c16017548 on 08/11/16.
 */
public interface FormulaVisitor<R> {

    public R visit(Variable variable);
    public R visit(Sum sum);
    public R visit(Product product);

}
