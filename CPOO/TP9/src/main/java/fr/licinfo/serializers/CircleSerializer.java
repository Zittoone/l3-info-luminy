package fr.licinfo.serializers;

import fr.licinfo.drawer.Circle;

/**
 * Created by c16017548 on 06/12/16.
 */
public class CircleSerializer implements ShapeSerializer<Circle> {

    public static CircleSerializer instance = new CircleSerializer();

    @Override
    public String code() {
        return "Circle";
    }

    @Override
    public String serialize(Circle shape) {
        StringBuilder serialized = new StringBuilder();

        serialized.append(this.code());
        serialized.append(" ");
        serialized.append(shape.x);
        serialized.append(" ");
        serialized.append(shape.y);
        serialized.append(" ");
        serialized.append(shape.radius);

        return serialized.toString();
    }

    @Override
    public Circle unserialize(String s) {
        String[] serialized = s.split(" ");

        if(!serialized[0].equals(this.code()))
            return null;
        double x = new Double(serialized[1]);
        double y = new Double(serialized[2]);
        double radius = new Double(serialized[3]);

        return new Circle(x, y, radius);
    }
}
