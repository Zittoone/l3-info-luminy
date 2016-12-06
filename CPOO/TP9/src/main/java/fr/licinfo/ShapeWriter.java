package fr.licinfo;

import fr.licinfo.drawer.Circle;
import fr.licinfo.drawer.Rectangle;
import fr.licinfo.drawer.Shape;
import fr.licinfo.serializers.CircleSerializer;
import fr.licinfo.serializers.RectangleSerializer;

import java.io.*;
import java.util.List;

/**
 * Created by c16017548 on 22/11/16.
 */
public class ShapeWriter implements ShapeVisitor<String> {

    private static ShapeWriter instance = new ShapeWriter();

    public static void write(File file, List<Shape> shapes) throws IOException {

        PrintWriter writer = new PrintWriter(file);

        for (Shape s : shapes) {
            String serialized = s.accept(instance);
            writer.println(serialized);
        }
        writer.close();
    }

    @Override
    public String visit(Rectangle r) {
        return RectangleSerializer.instance.serialize(r);
    }

    @Override
    public String visit(Circle c) {
        return CircleSerializer.instance.serialize(c);
    }
}
