package sample;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.MouseEvent;

/**
 * Created by c16017548 on 25/10/16.
 */
public interface DrawerState {

    public void mousePressed(MouseEvent event);

    public void mouseReleased(MouseEvent event);

    public void mouseMoved(MouseEvent event);

    public void paint(GraphicsContext context);
}
