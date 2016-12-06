package fr.licinfo.serializers;

import fr.licinfo.drawer.Rectangle;

/**
 * Created by c16017548 on 06/12/16.
 */
public class RectangleSerializer implements ShapeSerializer<Rectangle> {

    public static RectangleSerializer instance = new RectangleSerializer();

    @Override
    public String code() {
        return "Rectangle";
    }

    @Override
    public String serialize(Rectangle shape) {
        StringBuilder serialized = new StringBuilder();

        serialized.append(this.code());
        serialized.append(" ");
        serialized.append(shape.x);
        serialized.append(" ");
        serialized.append(shape.y);
        serialized.append(" ");
        serialized.append(shape.width);
        serialized.append(" ");
        serialized.append(shape.height);

        return serialized.toString();
    }

    @Override
    public Rectangle unserialize(String s) {
        String[] serialized = s.split(" ");

        if(!serialized[0].equals(this.code()))
            return null;
        double x = new Double(serialized[1]);
        double y = new Double(serialized[2]);
        double width = new Double(serialized[3]);
        double height = new Double(serialized[4]);

        return new Rectangle(x, y, width, height);
    }
}

