package fr.licinfo.acyclique;

import fr.licinfo.formula.Variable;

/**
 * Created by c16017548 on 08/11/16.
 */
public interface VariableVisitor<R> {
    public R visit(Variable variable);
}
