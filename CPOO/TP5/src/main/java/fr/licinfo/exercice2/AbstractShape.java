package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public abstract class AbstractShape implements Shape{

    private List<Point2D> points;

    public AbstractShape() {
        this.points = new ArrayList<Point2D>();
    }

    public void addPoints(Point2D... points){
        for (Point2D point : points) {
            this.points.add(point);
        }
    }

    public int pointsCount(){
        return this.points.size();
    }

    public Point2D point(int index){
        return this.points.get(index);
    }

    public abstract void draw(GraphicsContext graphicsContext);
}
