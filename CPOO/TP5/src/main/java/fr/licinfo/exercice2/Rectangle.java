package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public class Rectangle extends AbstractShape {

    private Color color;

    public Rectangle(Color color, Point2D... points){
        this.addPoints(points);
        this.color = color;
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {

        // TODO: finir fill rect 
        graphicsContext.fillRect();
        graphicsContext.setFill(color);

    }
}
