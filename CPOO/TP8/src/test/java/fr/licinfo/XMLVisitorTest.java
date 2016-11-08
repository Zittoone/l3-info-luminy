package fr.licinfo;

import fr.licinfo.acyclique.FormulaVisitor;
import fr.licinfo.acyclique.XMLVisitor;
import fr.licinfo.formula.Variable;
import fr.licinfo.formula.Formula;
import fr.licinfo.formula.Product;
import fr.licinfo.formula.Sum;
import org.junit.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;

/**
 * Created by c16017548 on 08/11/16.
 */
public class XMLVisitorTest {

    private FormulaVisitor<String> visitor = new XMLVisitor();

    @Test
    public void testVariable() {
        Formula formula = new Variable("x", 12);
        String result = formula.accept(visitor);
        assertThat(result, is(equalTo("<var>x</var>")));
    }

    @Test
    public void testProduct() {
        Formula x = new Variable("x", 12);
        Formula y = new Variable("y", 12);
        Formula product = new Product(x,y);
        String result = product.accept(visitor);
        assertThat(result, is(equalTo("<product><var>x</var><var>y</var></product>")));
    }

    @Test
    public void testSum() {
        Formula x = new Variable("x", 12);
        Formula y = new Variable("y", 12);
        Formula sum = new Sum(x,y);
        String result = sum.accept(visitor);
        assertThat(result, is(equalTo("<sum><var>x</var><var>y</var></sum>")));
    }

}