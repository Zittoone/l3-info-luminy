package fr.licinfo;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;

import fr.licinfo.exercice1.Product;
import fr.licinfo.exercice1.Sum;
import fr.licinfo.exercice1.Variable;
import org.junit.Test;

import static org.junit.Assert.*;

/**
 * Created by c16017548 on 20/09/16.
 */
public class FormulaTest {

    //TODO: Change all basics operator with VariadicOperator
    @Test
    public void testVariableAsString(){

        Variable var = new Variable("x", 5.0);
        assertThat(var.asString(), equalTo("x"));
    }

    @Test
    public void testVariableAsValue(){

        Variable var = new Variable("x", 5.0);
        assertThat(var.asValue(), closeTo(5.0, 1));
    }

    @Test
    public void testSumAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Sum sum = new Sum(var1, var2);
        assertThat(sum.asString(), equalTo("(x + y)"));
    }

    @Test
    public void testSumAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Sum sum = new Sum(var1, var2);
        assertThat(sum.asValue(), closeTo(7.0, 1));
    }

    @Test
    public void testProductAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 3.0);

        Product prod = new Product(var1, var2);
        assertThat(prod.asString(), equalTo("(x * y)"));
    }

    @Test
    public void testProductAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 3.0);

        Product prod = new Product(var1, var2);
        assertThat(prod.asValue(), closeTo(15.0, 1));
    }

}