package fr.licinfo;

import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import org.info.painter.EnglishPainter;

/**
 * Created by Alexis Couvreur on 03/10/2016.
 */
public class Truck extends Canvas {
    public Truck() {
        super(130,110);
        GraphicsContext graphicsContext = this.getGraphicsContext2D();
        EnglishPainter englishPainter =
                new EnglishPainter(graphicsContext);
        Painter painter = new EnglishPainterAdapter(englishPainter);

        //Painter painter = new FrenchPainter(graphicsContext);
        draw(painter);
    }

    private void draw(Painter painter) {
        painter.drawRectangle(10.0, 10.0, 70.0, 70.0);
        painter.drawRectangle(80.0, 45.0, 40.0, 35.0);
        painter.drawCircle(40.0, 80.0, 10.0);
        painter.drawCircle(100.0, 80.0, 10.0);
    }
}