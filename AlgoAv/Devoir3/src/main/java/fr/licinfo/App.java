package fr.licinfo;

import java.util.ArrayList;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) {
        ArrayList<Integer> vertices = new ArrayList<Integer>();
        vertices.add(1);
        vertices.add(2);
        vertices.add(3);
        vertices.add(4);

        ArrayList<Edge> edges = new ArrayList<Edge>();
        edges.add(new Edge(1, 2, 4));
        edges.add(new Edge(2, 3, 5));
        edges.add(new Edge(3, 4, 3));
        edges.add(new Edge(4, 2, 2));

        Graph graph = new Graph(vertices, edges);

        System.out.println(graph.toString());
    }
}
