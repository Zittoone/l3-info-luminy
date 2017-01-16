package fr.licinfo;

import java.awt.*;

/**
 * Created by c16017548 on 30/12/16.
 */
public class SquareDot extends Glyph{

    public SquareDot() {
        super();
    }

    public void draw(Graphics g, int x, int y, int size) {
        g.fillRect(x + 1, y + 1, size - 1, size - 1);
    }

}
