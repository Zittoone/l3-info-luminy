package fr.licinfo;

import fr.licinfo.drawer.Circle;
import fr.licinfo.drawer.Rectangle;

/**
 * Created by c16017548 on 06/12/16.
 */
public interface ShapeVisitor<T> {
    public T visit(Rectangle r);
    public T visit(Circle c);
}
