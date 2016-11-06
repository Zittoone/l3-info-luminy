package sample;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.MouseEvent;

/**
 * Created by c16017548 on 25/10/16.
 */
public interface DrawerState {

    public void mousePressed(DrawerContext context, double x, double y);
    public void mouseReleased(DrawerContext context, double x, double y);
    public void mouseMoved(DrawerContext context, double x, double y);
    public void paint(Drawer drawer);
    public boolean isInitialised();
}
