package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public abstract class Decorator implements Shape {

    protected Shape decoratedShape;

    public Decorator(Shape decoratedShape){
        this.decoratedShape = decoratedShape;
    }

    @Override
    public int pointsCount() {
        return decoratedShape.pointsCount();
    }

    @Override
    public Point2D point(int index) {
        return decoratedShape.point(index);
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {
        decoratedShape.draw(graphicsContext);
    }

    protected abstract void drawDecoration(GraphicsContext graphicsContext);

}
