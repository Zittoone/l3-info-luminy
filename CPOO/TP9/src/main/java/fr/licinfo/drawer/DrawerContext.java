package fr.licinfo.drawer;

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyCode;
import javafx.scene.input.MouseEvent;

public class DrawerContext {

    private DrawerState currentState;
    private Drawer drawer;

    public DrawerContext(Drawer drawer){
        this.drawer = drawer;
        currentState = new NullDrawerState();
        addEvents();
    }

    private void addEvents() {
        drawer.setOnMousePressed(event -> mousePressed(event));
        drawer.setOnMouseReleased(event -> mouseReleased(event));
        drawer.setOnMouseDragged(event -> mouseMoved(event));

    }

    public void paint(GraphicsContext graphicsContext){
        drawer.repaint();
    }

    public void mousePressed(MouseEvent event) {
        currentState.mousePressed(this, event.getX(), event.getY());
    }

    public void mouseReleased(MouseEvent event) {
        if (!currentState.isInitialised())
            return;
        currentState.mouseReleased(this, event.getX(), event.getY());
    }

    public void mouseMoved(MouseEvent event) {
        if (!currentState.isInitialised())
            mousePressed(event);
        currentState.mouseMoved(this, event.getX(), event.getY());
    }

    public Drawer drawer(){
        return this.drawer;
    }


    public void setState(KeyCode k) {
        switch (k) {
            case C:
                currentState = new CircleDrawerState();
                break;
            case R:
                currentState = new RectangleDrawerState();
                break;
            case M:
                currentState = new MoveDrawerState();
                break;
            default:
                currentState = new NullDrawerState();
        }
    }
}
