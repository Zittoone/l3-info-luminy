package fr.licinfo.exercice1;

import javafx.scene.canvas.GraphicsContext;

/**
 * Created by Alexis Couvreur on 03/10/2016.
 */
public class FrenchPainter implements Painter {

    GraphicsContext gc;

    public FrenchPainter(GraphicsContext graphicsContext) {
        this.gc = graphicsContext;
    }

    public void drawRectangle(double v, double v1, double v2, double v3) {
        this.gc.strokeRect(v, v1, v2, v3);
    }

    public void drawCircle(double v, double v1, double v2) {
        this.gc.strokeOval(v, v1, v2, v2);
    }

}
