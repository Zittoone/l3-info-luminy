package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public class Rectangle extends AbstractShape {

    private Color color;

    public Rectangle(Color color, Point2D point1, Point2D point2){
        this.addPoints(point1, point2);
        this.color = color;
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        graphicsContext.setFill(color);
        Point2D p0= point (0);
        Point2D p1= point (1);
        double x= Math.min (p0.getX(), p1.getX());
        double y= Math.min (p0.getY(), p1.getY());
        double w= Math.abs (p1.getX() - p0.getX());
        double h= Math.abs (p1.getY() - p0.getY());
        graphicsContext.fillRect(x, y, w, h);


    }
}
