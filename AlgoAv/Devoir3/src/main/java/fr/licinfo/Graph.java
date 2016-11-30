package fr.licinfo;

import java.util.List;
import java.util.Set;

/**
 * Created by c16017548 on 30/11/16.
 */
public interface Graph {

    public void addEdge(Edge e);
    public void addNode(Integer node);
    public List<Edge> adjacent(Integer node);
    public void clear();
    public Object clone();
    public boolean containsEdge(Edge e);
    public boolean containsNode(Integer node);
    public List<Edge> getEdges();
    public Set<Integer> getNodes();
    public List<Edge> incident(Integer node);
    public int numEdges();
    public int numNodes();
    public void removeEdge(Edge e);
    public void removeNode(Integer node);



}
