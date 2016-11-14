package fr.licinfo.acyclique;

import fr.licinfo.formula.Product;

/**
 * Created by c16017548 on 08/11/16.
 */
public interface ProductVisitor<R> {
    public R visit(Product product);
}
