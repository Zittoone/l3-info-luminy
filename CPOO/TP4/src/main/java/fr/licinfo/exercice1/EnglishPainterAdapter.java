package fr.licinfo.exercice1;

import javafx.geometry.Point2D;
import org.info.painter.EnglishPainter;

/**
 * Created by c16017548 on 04/10/16.
 */
public class EnglishPainterAdapter implements Painter{

    EnglishPainter ep;

    public EnglishPainterAdapter(EnglishPainter englishPainter) {
        this.ep = englishPainter;
    }

    public void drawRectangle(double v, double v1, double v2, double v3) {
        this.ep.paintRectangle(new Point2D(v, v1), new Point2D(v + v2, v1 + v3));
    }

    public void drawCircle(double v, double v1, double v2) {
        this.ep.paintCircle(new Point2D(v, v1), new Point2D(v + v2, v1));
    }
}
