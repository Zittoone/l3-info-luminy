package fr.licinfo.exercice1;

/**
 * Created by c16017548 on 27/09/16.
 */
public abstract class VariadicOperator implements Formula{

    private Operator operator;
    private Formula[] formulas;

    public VariadicOperator(Operator operator, Formula... formulas){
        this.formulas = formulas;
        this.operator = operator;
    }

    @Override
    public String asString() {

        String str = "";

        for (int i = 0; i < formulas.length; i++){
            str += formulas[i].asString();

            if (i != formulas.length - 1){
                str += operator.symbol();
            }

        }

        return "(" + str + ")";
    }

    @Override
    public Double asValue() {
        double dbl = operator.initialValue();

        for (Formula aVarTab : formulas) {
            dbl = operator.cumulativeValue(dbl, aVarTab.asValue());
        }

        return dbl;
    }

}
