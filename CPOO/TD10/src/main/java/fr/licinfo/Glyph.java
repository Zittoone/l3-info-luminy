package fr.licinfo;

import java.awt.*;

/**
 * Created by c16017548 on 30/12/16.
 */
public class Glyph implements Drawable{

    /*public enum DotType { Square, Circle }
    private DotType type;*/

    private char[][] matrix;
    private Glyph glyph;

    /*public Glyph(char[][] matrix, DotType type) {
        this.matrix = matrix; this.type = type;
    }*/

    public Glyph(char[][] matrix, Glyph glyph){
        this.glyph = glyph;
        this.matrix = matrix;
    }

    public Glyph() {

    }

    public void draw(Graphics g, int x, int y, int size) {
        int n = matrix.length;
        int ds = size / n;
        for (int px = 0; px < n; px++)
            for (int py = 0; py < n; py++)
                if (matrix[py][px] == '#')
                    glyph.draw(g, x + px * ds + 1, y + py * ds + 1, ds - 1);
    }

    /*
    private void drawDot(Graphics g, int x, int y, int size) {
        switch (type) {
            case Square: drawSquare(g, x, y, size); break;
            case Circle: drawCircle(g, x, y, size); break;
        }
    }
    private void drawSquare(Graphics g, int x, int y, int size) {
        g.fillRect(x + 1, y + 1, size - 1, size - 1);
    }
    private void drawCircle(Graphics g, int x, int y, int size) {
        g.fillOval(x, y, size, size);
    }*/
}