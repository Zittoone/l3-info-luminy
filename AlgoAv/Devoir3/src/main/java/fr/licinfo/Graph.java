package fr.licinfo;


import java.util.ArrayList;
import java.util.List;

/**
 * Created by sebastientosello on 23/11/2016.
 */
public class Graph {
    private List<List<Edge>> incidences;

    public Graph(){
        this.incidences = new ArrayList<List<Edge>>();
    }

    public Graph(int verticesNumber){
        this.incidences = new ArrayList<List<Edge>>(verticesNumber);
    }

    public void setVertice(int i, List<Edge> list){
        this.incidences.add(i, list);
    }

    public void addVertice(List<Edge> list){
        this.incidences.add(list);
    }

    public void addEdge(int vertice, Edge edge){

    }

    public void addEdges(int vertice, List<Edge> edges){

    }
    
    public String toString(){
        return "Vertices : " + vertices.toString() + "\nEdges : " + edges.toString();
    }
}
