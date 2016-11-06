package fr.licinfo.exercice1;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;

import fr.licinfo.exercice1.Product;
import fr.licinfo.exercice1.Sum;
import fr.licinfo.exercice1.Variable;
import fr.licinfo.exercice1.VariadicOperator;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by c16017548 on 20/09/16.
 */
public class FormulaTest {

    @Test
    public void testVariadicOperatorAsString(){

        VariadicOperator var = new VariadicOperator(new Sum(), new Variable("x", 5.0), new Variable("y", 6.0));
        assertThat(var.asString(), equalTo("(x + y)"));
    }

    @Test
    public void testVariadicOperatorAsValue(){

        Variable var = new Variable("x", 5.0);
        assertThat(var.asValue(), closeTo(5.0, 1));
    }

    @Test
    public void testSumAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Sum sum = new Sum(var1, var2);

        VariadicOperator varop = new VariadicOperator(sum, var1, var2);
        assertThat(varop.asString(), equalTo("(x + y)"));
    }

    @Test
    public void testSumAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Sum sum = new Sum(var1, var2);
        VariadicOperator varop = new VariadicOperator(sum, var1, var2);
        assertThat(varop.asValue(), closeTo(7.0, 1));
    }

    @Test
    public void testProductAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 3.0);

        Product prod = new Product(var1, var2);

        VariadicOperator varop = new VariadicOperator(prod, var1, var2);
        assertThat(varop.asString(), equalTo("(x * y)"));
    }

    @Test
    public void testProductAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 3.0);

        Product prod = new Product(var1, var2);

        VariadicOperator varop = new VariadicOperator(prod, var1, var2);
        assertThat(varop.asValue(), closeTo(15.0, 1));
    }

}