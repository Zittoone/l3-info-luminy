package fr.licinfo.drawer;


import fr.licinfo.ShapeReader;
import fr.licinfo.ShapeWriter;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Alert;
import javafx.stage.FileChooser;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Created by c16017548 on 25/10/16.
 */
public class Drawer extends Canvas {

    private List<Shape> shapes;
    //private DrawerContext context;

    public Drawer(double width, double height){
        super(width, height);
        shapes = new ArrayList<Shape>();
    }

    public void add(Shape shape){
        shapes.add(shape);
    }

    public void repaint(){
        GraphicsContext gc = this.getGraphicsContext2D();

        //gc.clearRect(0, 0, this.getWidth(), this.getHeight());

        for (Shape s: shapes) {
            s.paint(gc);
        }
    }

    public Shape shapesContaining(double x, double y) {
        for (Shape s : shapes)
            if (s.contains(x, y))
                return s;
        return null;
    }

    public void save(File f){
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Save");
        File file = fileChooser.showSaveDialog(getScene().getWindow());
        if (file == null) return;
        try {
            ShapeWriter.write(file, shapes);
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error Dialog");
            alert.setHeaderText(null);
            alert.setContentText("Ooops, there was an error!");
            alert.showAndWait();
        }
    }

    public void load() {
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Load");
        File file = fileChooser.showOpenDialog(getScene().getWindow());
        if (file == null) return;
        try {
            shapes = ShapeReader.read(file, Collectors.toList());
            repaint();
        } catch (IOException e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error Dialog");
            alert.setHeaderText(null);
            alert.setContentText("Ooops, there was an error!");
            alert.showAndWait();
        }
    }
}
