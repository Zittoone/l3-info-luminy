package fr.licinfo.drawer;

import fr.licinfo.ShapeVisitor;
import javafx.scene.canvas.GraphicsContext;

/**
 * Created by c16017548 on 25/10/16.
 */
public interface Shape {
    public void paint(GraphicsContext graphicsContext);
    public boolean contains(double x, double y);
    public void translate(double dx, double dy);

    public <R> R accept(ShapeVisitor<R> sv);
}
