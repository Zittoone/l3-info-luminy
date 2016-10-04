package fr.licinfo;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.*;

import fr.licinfo.formula.*;
import org.hamcrest.core.IsInstanceOf;
import org.junit.Rule;
import org.junit.Test;

import junit.framework.TestCase;
import org.junit.rules.ExpectedException;

import static org.junit.Assert.*;

/**
 * Created by c16017548 on 20/09/16.
 */
public class FormulaTest {

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

    @Test
    public void testAbsoluteValueAsString(){

        Variable var = new Variable("x", -5.0);

        AbsoluteValue abs = new AbsoluteValue(var);
        assertThat(abs.asString(), equalTo("|x|"));

    }

    @Test
    public void testAbsoluteValueAsValue(){

        Variable var = new Variable("x", -5.0);

        AbsoluteValue abs = new AbsoluteValue(var);
        assertThat(abs.asValue(), closeTo(5.0, 1));
    }

    @Test
    public void testMaximumAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Maximum max = new Maximum(var1, var2);
        assertThat(max.asString(), equalTo("x"));
    }

    @Test
    public void testMaximumAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Maximum max = new Maximum(var1, var2);
        assertThat(max.asValue(), closeTo(5.0, 1));
    }

    @Test
    public void testMinimumAsString(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Minimum max = new Minimum(var1, var2);
        assertThat(max.asString(), equalTo("y"));
    }

    @Test
    public void testMinimumAsValue(){

        Variable var1 = new Variable("x", 5.0);
        Variable var2 = new Variable("y", 2.0);

        Minimum max = new Minimum(var1, var2);
        assertThat(max.asValue(), closeTo(2.0, 1));
    }

    @Test
    public void testPowerAsString(){

        Variable var = new Variable("x", 5.0);

        Power pow = new Power(var, 2.0);
        assertThat(pow.asString(), equalTo("x^2.0"));
    }

    @Test
    public void testPowerAsValue(){

        Variable var = new Variable("x", 5.0);

        Power pow = new Power(var, 2.0);
        assertThat(pow.asValue(), closeTo(25.0, 1));
    }

    @Test
    public void testSquareAsString(){

        Variable var = new Variable("x", 5.0);

        Square sq = new Square(var);
        assertThat(sq.asString(), equalTo("x^2"));
    }

    @Test
    public void testSquareAsValue(){

        Variable var = new Variable("x", 5.0);

        Square sq = new Square(var);
        assertThat(sq.asValue(), closeTo(25.0, 1));
    }

    @Test
    public void testSquareRootAsString(){

        Variable var = new Variable("x", 4.0);

        SquareRoot sqrt = new SquareRoot(var);
        assertThat(sqrt.asString(), equalTo("sqrt(x)"));
    }

    @Test
    public void testSquareRootAsValue(){

        Variable var = new Variable("x", 4.0);

        SquareRoot sqrt = new SquareRoot(var);
        assertThat(sqrt.asValue(), closeTo(2.0, 1));
    }

}