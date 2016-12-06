package fr.licinfo;

import fr.licinfo.drawer.Shape;
import fr.licinfo.serializers.CircleSerializer;
import fr.licinfo.serializers.RectangleSerializer;
import fr.licinfo.serializers.ShapeSerializer;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * Created by c16017548 on 22/11/16.
 */
public class ShapeReader {

    private static Map<String, ShapeSerializer<? extends Shape>> map = new HashMap<String, ShapeSerializer<?>>();

    static {
        map.put(CircleSerializer.instance.code(),
                CircleSerializer.instance);
        map.put(RectangleSerializer.instance.code(),
                RectangleSerializer.instance);
    }

    public static void add(ShapeSerializer<?> ss) {
        map.put(ss.code(), ss);
    }

    private static Shape scanLine(String line) throws IOException {
        Scanner scanner = new Scanner(line);
        String code = scanner.next();
        ShapeSerializer<?> s = map.get(code);
        if(s == null) throw new IOException();
        return s.unserialize(line);
    }

    public static List<Shape> read(File file) throws IOException {

        List<Shape> shapes = new ArrayList<>();

        try {
            BufferedReader br = new BufferedReader(new FileReader(file));
            String line = null;
            while((line = br.readLine()) != null){
                Shape shape = scanLine(line);
                shapes.add(shape);
            }
        } catch (IOException e){
            System.out.println("Error reading file");
        }

        return shapes;
    }
}
