package fr.licinfo;

import fr.licinfo.drawer.Circle;
import fr.licinfo.drawer.Shape;
import sun.security.provider.SHA;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;
import java.util.function.Supplier;
import java.util.stream.Collector;

/**
 * Created by c16017548 on 22/11/16.
 */
public class ShapeReader {

    public static List<Shape> read(File file, Collector<Shape, ?, List<Shape>> collector) throws IOException {

        BufferedReader br = new BufferedReader(new FileReader(file));
        //objectListCollector.
        Supplier<?> container = collector.supplier().get();
        collector.accumulator().accept(container, new Circle(2, 2, 2));

        container.get().
        for (T t : data)
            collector.accumulator().accept(container, t);
        return collector.finisher().apply(container);

        Supplier<?> sup = collector.supplier();
        collector.

        String line;

        while ((line = br.readLine()) != null){
            // TODO: traiter ligne par ligne les informations et créer les formes
        }



    }
}
