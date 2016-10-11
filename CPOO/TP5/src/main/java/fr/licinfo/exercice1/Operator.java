package fr.licinfo.exercice1;

/**
 * Created by c16017548 on 11/10/16.
 */
public interface Operator {

    String symbol();
    double initialValue();
    double cumulativeValue(double acc, double value);
}
