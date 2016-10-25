package sample;


import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.MouseEvent;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by c16017548 on 25/10/16.
 */
public class Drawer extends Canvas {

    private List<Shape> shapes;
    private DrawerContext context;

    public Drawer(double width, double height){
        super(width, height);
        this.context = new DrawerContext();
        shapes = new ArrayList<Shape>();

        addEventHandler(MouseEvent.MOUSE_PRESSED,
                context::mousePressed);

        addEventHandler(MouseEvent.MOUSE_MOVED,
                context::mouseMoved);

        addEventHandler(MouseEvent.MOUSE_RELEASED,
                context::mouseReleased);



    }

    public void add(Shape shape){
        shapes.add(shape);
    }

    public void repaint(){
        GraphicsContext gc = this.getGraphicsContext2D();

        gc.clearRect(0, 0, this.getWidth(), this.getHeight());

        for (Shape s: shapes) {
            s.paint(gc);
        }
    }

    public void shapeContaining(double x, double y){

    }
}
