package fr.licinfo;

import javax.swing.*;
import java.awt.*;

/**
 * Created by c16017548 on 30/12/16.
 */
public class Picture extends JPanel {

    char[][] c2 = {
            {' ',' ','#',' ',' '},
            {' ','#',' ','#',' '},
            {' ','#',' ','#',' '},
            {'#','#',' ','#','#'},
            {'#','#','#','#','#'}};
    char[][] c3 =  {
            {' ',' ','#',' ',' '},
            {' ','#',' ','#',' '},
            {' ','#',' ','#',' '},
            {'#','#',' ','#','#'},
            {'#','#','#','#','#'}};

    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Drawable glyphC = new CircleDot();
        Drawable glyphS = new SquareDot();
        Drawable glyph2 = new Glyph(c2, new SquareDot());
        Drawable glyph3 = new Glyph(c3, new CircleDot());
        Drawable glyph22 = new Glyph(c2,
                new Glyph(c2,
                        new Glyph(c3, new SquareDot())));
        Drawable glyph33 = new Glyph(c3,
                new Glyph(c3, new SquareDot()));
        glyph22.draw(g, 10, 10, 1500);
    }
}
