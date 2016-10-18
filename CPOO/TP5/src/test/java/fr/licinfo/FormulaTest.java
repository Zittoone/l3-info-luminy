package fr.licinfo;

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
    public void testSumAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        VariadicOperator vo = new VariadicOperator(new Sum(), var1, var2);
        assertThat(vo.asString(), equalTo("(x + y)"));
    }

    @Test
    public void testSumAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        VariadicOperator vo = new VariadicOperator(new Sum(), var1, var2);
        assertThat(vo.asValue(), closeTo(7.0, 1));
    }

    @Test
    public void testProductAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 3.0);

        VariadicOperator vo = new VariadicOperator(new Product(), var1, var2);
        assertThat(vo.asString(), equalTo("(x * y)"));
    }

    @Test
    public void testProductAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 3.0);

        VariadicOperator vo = new VariadicOperator(new Product(), var1, var2);
        assertThat(vo.asValue(), closeTo(15.0, 1));
    }

}