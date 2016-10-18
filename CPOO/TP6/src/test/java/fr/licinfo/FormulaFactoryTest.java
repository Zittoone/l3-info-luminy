package fr.licinfo;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.equalTo;
import static org.hamcrest.Matchers.is;

import fr.licinfo.formula.*;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import org.junit.runners.Parameterized.Parameters;

//@RunWith(Parameterized.class)
public class FormulaFactoryTest {

    @Parameters
    public static Object[] data() {
        return new Object[] {
                new ExtensionFormulaFactory(),
                new StrategyFormulaFactory()
        };
    }

    @Parameter
    public AbstractFormulaFactory factory = new StrategyFormulaFactory();

    @Test
    public void createSum() {
        Formula formula = factory.createSum(new Constant(2), new Constant(3));
        assertThat(formula.asValue(), is(equalTo(5.0)));
        assertThat(formula.asString(), is(equalTo("(2.0+3.0)")));
    }

}