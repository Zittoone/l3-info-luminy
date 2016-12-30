package fr.licinfo;

import java.awt.*;

/**
 * Created by c16017548 on 30/12/16.
 */
public class CircleDot extends Glyph {

    public CircleDot() {
        super();
    }

    public void draw(Graphics g, int x, int y, int size) {
        g.fillOval(x, y, size, size);
    }
}
