package fr.licinfo;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

/**
 * Created by c16017548 on 30/11/16.
 */
public class FlowGraph implements Graph{

    private List<List<Edge>> incidences;

    public FlowGraph(){
        incidences = new ArrayList<List<Edge>>();
    }

    public void addEdge(Edge e) {

        // getSource équivaut à l'index et donc le numéro du sommet
        List<Edge> source = incidences.get(e.getSource());

        if(source != null){
            source.add(e);
        } else {
            this.addNode(e.getSource());
            this.addEdge(e);
        }
    }

    public void addNode(Integer node) {
        incidences.set(node, new ArrayList<Edge>());
    }

    public List<Edge> adjacent(Integer node) {
        return incidences.get(node);
    }

    public void clear() {
        incidences.clear();
    }

    public Object clone() {
        return null;
    }

    public boolean containsEdge(Edge e) {
        return incidences.get(e.getSource()) != null;
    }

    public boolean containsNode(Integer node) {
        return incidences.get(node) != null;
    }

    public List<Edge> getEdges() {
        List<Edge> edges = new ArrayList<Edge>();

        for (List<Edge> list : incidences) {
            edges.addAll(list);
        }
        return edges;
    }

    public Set<Integer> getNodes() {
        Set<Integer> nodes = new TreeSet<Integer>();

        for (List<Edge> node : incidences)
            nodes.add(incidences.indexOf(node));

        return nodes;
    }

    public List<Edge> incident(Integer node) {
        return incidences.get(node);
    }

    public int numEdges() {
        int numEdges = 0;
        for (List<Edge> node : incidences){
            numEdges += node.size();
        }
        return numEdges;
    }

    public int numNodes() {
        return incidences.size();
    }

    public void removeEdge(Edge e) {
        incidences.get(e.getSource()).remove(e);
    }

    public void removeNode(Integer node) {
        incidences.get(node).clear();
        incidences.remove(node);
    }
}
