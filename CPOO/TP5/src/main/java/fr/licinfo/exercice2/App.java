package fr.licinfo.exercice2;

import javafx.application.Application;
import javafx.geometry.Point2D;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

/**
 * Created by c16017548 on 18/10/16.
 */
public class App extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();

        Canvas canvas = new Canvas(350, 350);

        ShapeContainer container = new ShapeContainer();
        Rectangle rect = new Rectangle(Color.RED, new Point2D(20, 10), new Point2D(100, 80));
        container.add(rect);

        Polygon poly = new Polygon(Color.BLUE, new Point2D(20, 100), new Point2D(100, 200), new Point2D(45, 260), new Point2D(20,200));
        container.add(poly);

        container.draw(canvas.getGraphicsContext2D());

        BorderDecorator bd = new BorderDecorator(rect, 5);
        bd.drawDecoration(canvas.getGraphicsContext2D());

        CenterDecorator cd = new CenterDecorator(rect, 5);
        cd.drawDecoration(canvas.getGraphicsContext2D());

        BorderDecorator bd2 = new BorderDecorator(poly, 5);
        bd2.drawDecoration(canvas.getGraphicsContext2D());

        CenterDecorator cd2 = new CenterDecorator(poly, 5);
        cd2.drawDecoration(canvas.getGraphicsContext2D());

        root.getChildren().add(canvas);
        primaryStage.setScene(new Scene(root));
        primaryStage.show();
    }
}
