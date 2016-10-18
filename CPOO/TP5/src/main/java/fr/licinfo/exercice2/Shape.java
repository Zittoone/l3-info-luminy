package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public interface Shape {

    int pointsCount();
    Point2D point(int index);
    void draw(GraphicsContext graphicsContext);

}
