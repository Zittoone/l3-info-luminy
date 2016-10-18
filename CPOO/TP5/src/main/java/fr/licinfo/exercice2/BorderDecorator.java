package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public class BorderDecorator extends Decorator {

    private double radius;

    public BorderDecorator(Shape decoratedShape, double radius) {
        super(decoratedShape);
        this.radius = radius;
    }

    @Override
    protected void drawDecoration(GraphicsContext graphicsContext) {
        for(int i = 0; i < decoratedShape.pointsCount(); i++){
            Point2D point = decoratedShape.point(i);
            graphicsContext.strokeOval(point.getX() - radius, point.getY() - radius, 2*radius, 2*radius);

        }
    }

}
