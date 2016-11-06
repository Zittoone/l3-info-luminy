package fr.licinfo;

import fr.licinfo.formula.AbstractFormulaFactory;
import fr.licinfo.formula.Formula;

import java.util.Stack;

/**
 * Created by sebastientosello on 18/10/2016.
 */
public class Calculator {

    private AbstractFormulaFactory factory;

    public Calculator(AbstractFormulaFactory factory){
        this.factory = factory;
    }

    public Formula analyze(String... tokens){

        Stack<Formula> stack = new Stack<Formula>();

        for (String s: tokens) {
            analyzeToken(s, stack);
        }

        return stack.pop();

    }

    private void analyzeToken(String token, Stack<Formula> stack){

        if(token.equals("+")){
            analyzeSum(stack);
        } else if(token.equals("*")){
            analyzeProduct(stack);
        } else {
            analyzeDouble(token, stack);
        }

    }

    private void analyzeSum(Stack<Formula> stack){
        Formula right = stack.pop();
        Formula left = stack.pop();
        Formula sum = factory.createSum(left, right);
        stack.push(sum);
    }

    private void analyzeProduct(Stack<Formula> stack){
        Formula right = stack.pop();
        Formula left = stack.pop();
        Formula prod = factory.createProduct(left, right);
        stack.push(prod);
    }

    private void analyzeDouble(String token, Stack<Formula> stack){
        Double value = Double.parseDouble(token);
        Formula c = factory.createConstant(value);
        stack.push(c);
    }
}
