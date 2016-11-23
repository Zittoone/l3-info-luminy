package fr.licinfo.drawer;

/**
 * Created by c16017548 on 25/10/16.
 */
public class NullDrawerState implements DrawerState {

    public void mousePressed(DrawerContext context, double x, double y) {
        System.out.println("null state");

    }

    public void mouseReleased(DrawerContext context, double x, double y) {
        return;

    }

    public void mouseMoved(DrawerContext context, double x, double y) {
        return;

    }

    public void paint(Drawer drawer) {
        return;

    }

    public boolean isInitialised() {
        return true;
    }
}
