package fr.licinfo.serializers;

import fr.licinfo.drawer.Shape;

/**
 * Created by c16017548 on 06/12/16.
 */
public interface ShapeSerializer<S extends Shape> {
    public String code();
    public String serialize(S shape);
    public S unserialize(String s);
}
