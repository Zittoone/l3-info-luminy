package sample;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

public class App extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        Drawer container = new Drawer(800, 600);

        GraphicsContext gc = container.getGraphicsContext2D();


        root.getChildren().add(container);
        primaryStage.setScene(new Scene(root));
        primaryStage.show();

        Shape s1 = new Rectangle(10, 10, 50, 60);
        Shape s2 = new Circle(40, 10, 80);
        container.add(s1);
        container.add(s2);
        container.repaint();
    }
}