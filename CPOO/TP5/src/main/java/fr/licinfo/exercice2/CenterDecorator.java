package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public class CenterDecorator extends Decorator {

    private double radius;

    public CenterDecorator(Shape decoratedShape, double radius) {
        super(decoratedShape);
        this.radius = radius;
    }

    @Override
    protected void drawDecoration(GraphicsContext graphicsContext) {

    }

}
