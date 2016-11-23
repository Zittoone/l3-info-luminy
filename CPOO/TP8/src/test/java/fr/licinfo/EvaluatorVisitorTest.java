package fr.licinfo;

import fr.licinfo.acyclique.EvaluatorVisitor;
import fr.licinfo.acyclique.FormulaVisitor;
import fr.licinfo.formula.Formula;
import fr.licinfo.formula.Product;
import fr.licinfo.formula.Sum;
import fr.licinfo.formula.Variable;
import org.junit.Test;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.core.Is.is;
import static org.hamcrest.core.IsEqual.equalTo;

/**
 * Created by c16017548 on 08/11/16.
 * Tests réalisés avec la version acyclique
 */
public class EvaluatorVisitorTest {

    private FormulaVisitor<Double> visitor = new EvaluatorVisitor();

    @Test
    public void testVariable() {
        Formula formula = new Variable("x", 12);
        double result = formula.accept(visitor);
        assertThat(result, is(equalTo(12.0)));
    }

    @Test
    public void testProduct() {
        Formula x = new Variable("x", 2);
        Formula y = new Variable("y", 3);
        Formula product = new Product(x,y);
        double result = product.accept(visitor);
        assertThat(result, is(equalTo(6.0)));
    }

    @Test
    public void testSum() {
        Formula x = new Variable("x", 2);
        Formula y = new Variable("y", 3);
        Formula sum = new Sum(x,y);
        double result = sum.accept(visitor);
        assertThat(result, is(equalTo(5.0)));
    }

}