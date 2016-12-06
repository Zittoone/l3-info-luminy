package fr.licinfo.drawer;

import fr.licinfo.ShapeVisitor;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by c16017548 on 25/10/16.
 */
public class Rectangle implements Shape {

    public double x,y, width, height;

    public Rectangle(double x, double y, double width, double height){
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    @Override
    public void paint(GraphicsContext graphicsContext) {
        graphicsContext.setFill(Color.rgb(200,0,0,0.5));
        graphicsContext.fillRect(x, y, width, height);
        graphicsContext.strokeRect(x, y, width, height);
    }

    @Override
    public boolean contains(double x, double y) {
        return (x >= this.x && x <= this.width) && (y >= this.y && y <= this.height);
    }

    @Override
    public void translate(double dx, double dy) {
        x += dx;
        y += dy;
    }

    @Override
    public <R> R accept(ShapeVisitor<R> sv) {
        return sv.visit(this);
    }
}
