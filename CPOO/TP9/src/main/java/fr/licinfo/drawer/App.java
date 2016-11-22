package fr.licinfo.drawer;

import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class App extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        Group root = new Group();
        Drawer container = new Drawer(800, 600);
        DrawerContext drawerContext = new DrawerContext(container);

        root.getChildren().add(container);

        Scene scene = new Scene(root);

        scene.setOnKeyPressed(event -> drawerContext.setState(event.getCode()));

        primaryStage.setScene(scene);
        primaryStage.show();
    }
}