package fr.licinfo;

import java.io.IOException;
import java.io.Writer;

/**
 * Created by c16017548 on 27/09/16.
 */
public class Curve {

    private Function fonction;
    private double startValue, endValue, step;

    public Curve(Function fonction, double start, double end, double step){
        this.fonction = fonction;
        this.startValue = start;
        this.endValue = end;
        this.step = step;
    }

    public void writePoints(Writer writer){

        StringBuilder stringBuilder = new StringBuilder();

        for (double value = startValue; value <= endValue; value+=step) {

            this.fonction.getVariable().set(value);
            stringBuilder.append(value+" "+fonction.process()+"\n");

        }

        try {
            writer.append(stringBuilder);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
