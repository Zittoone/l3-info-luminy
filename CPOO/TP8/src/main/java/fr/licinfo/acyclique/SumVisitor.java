package fr.licinfo.acyclique;

import fr.licinfo.formula.Sum;

/**
 * Created by c16017548 on 08/11/16.
 */
public interface SumVisitor<R> {
    public R visit(Sum sum);
}
