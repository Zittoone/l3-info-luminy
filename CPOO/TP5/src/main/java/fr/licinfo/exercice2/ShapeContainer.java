package fr.licinfo.exercice2;

import javafx.scene.canvas.GraphicsContext;

import java.util.List;

/**
 * Created by Alexis Couvreur on 11/10/2016.
 */
public class ShapeContainer {

    private List<Shape> shapes;

    public void add(Shape shape){
        shapes.add(shape);
    }

    public void draw(GraphicsContext graphicsContext){

    }
}
