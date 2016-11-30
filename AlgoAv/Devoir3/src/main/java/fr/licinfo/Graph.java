package fr.licinfo;


import java.util.ArrayList;
import java.util.List;

/**
 * Created by sebastientosello on 23/11/2016.
 */
public class Graph {
    private List<List<Edge>> incidences;

    public Graph() {
        this.incidences = new ArrayList<List<Edge>>();
    }

    public Graph(int verticesNumber) {
        this.incidences = new ArrayList<List<Edge>>(verticesNumber);
    }

    public void setVertice(int i, List<Edge> list) {
        this.incidences.add(i, list);
    }

    public void addVertice(List<Edge> list) {
        this.incidences.add(list);
    }

    public void addEdge(int vertice, Edge edge) {
        this.incidences.get(vertice).add(edge);
    }

    public void addEdges(int vertice, List<Edge> edges) {
        this.incidences.get(vertice).addAll(edges);
    }

    public List<Edge> getEdges(int vertice) {
        return this.incidences.get(vertice);
    }
}
