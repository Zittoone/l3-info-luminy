package sample;

import javafx.event.Event;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;

public class DrawerContext {

    DrawerState currentState;
    Drawer drawer;

    public void paint(GraphicsContext graphicsContext){

    }

    public void mousePressed(MouseEvent event) {
        System.out.println("mp: " + event.getX() + " " + event.getY());
    }

    public void mouseReleased(MouseEvent event) {
        System.out.println("mr: " + event.getX() + " " + event.getY());
    }

    public void mouseMoved(MouseEvent event) {
        //System.out.println("mm: " + event.getX() + " " + event.getY());
    }

    public void keyPressed(KeyEvent event){

    }

    public Drawer drawer(){
        return this.drawer;
    }




}
