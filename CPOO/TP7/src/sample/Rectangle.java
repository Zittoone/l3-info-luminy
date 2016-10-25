package sample;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by c16017548 on 25/10/16.
 */
public class Rectangle implements Shape {

    private double x,y, width, height;

    public Rectangle(double x, double y, double width, double height){
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    @Override
    public void paint(GraphicsContext graphicsContext) {
        graphicsContext.setFill(new Color(0.228, 0.139, 0.139, 0.4));
        graphicsContext.fillRect(x, y, width, height);
    }

    @Override
    public boolean contains(double x, double y) {
        return (x >= this.x && x <= this.width) && (y >= this.y && y <= this.height);
    }

    @Override
    public void translate(double dx, double dy) {

    }
}
