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
        Point2D center;

        double x = 0, y = 0;
        for(int i = 0; i < decoratedShape.pointsCount(); i++){
            x+=decoratedShape.point(i).getX();
            y+=decoratedShape.point(i).getY();
        }

        center = new Point2D(x / decoratedShape.pointsCount(), y / decoratedShape.pointsCount());

        graphicsContext.strokeOval(center.getX() - radius, center.getY() - radius, radius*2, radius*2);
    }

}
