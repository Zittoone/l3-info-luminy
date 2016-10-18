package fr.licinfo.exercice2;

import javafx.geometry.Point2D;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public class Polygon extends AbstractShape {

    private Color color;

    public Polygon(Color color, Point2D... points){
        this.addPoints(points);
        this.color = color;
    }

    @Override
    public void draw(GraphicsContext graphicsContext) {

        graphicsContext.setFill(color);

        int n = pointsCount();
        double[] xs = new double[n],
                 ys = new double[n];

        for (int i = 0; i < n; i++){
            xs[i] = point(i).getX();
            ys[i] = point(i).getY();
        }

        graphicsContext.fillPolygon(xs, ys, n);

    }
}
