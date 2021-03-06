package sample;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by c16017548 on 25/10/16.
 */
public class Circle implements Shape {

    private double x,y, radius;

    public Circle(double x, double y, double radius){
        this.x = x;
        this.y = y;
        this.radius = radius;
    }

    @Override
    public void paint(GraphicsContext graphicsContext) {
        graphicsContext.setFill(Color.rgb(0,200,0,0.5));
        graphicsContext.fillOval(x, y, radius, radius);
        graphicsContext.strokeOval(x, y, radius, radius);
    }

    @Override
    public boolean contains(double x, double y) {
        return Math.hypot(this.x - x, this.y - y) <= this.radius;
    }

    @Override
    public void translate(double dx, double dy) {
        x += dx;
        y += dy;
    }
}
