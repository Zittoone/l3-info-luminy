package fr.licinfo;

/**
 * Created by sebastientosello on 23/11/2016.
 */
public class Edge {
    private int connectedVertice, weight;

    public Edge(int connectedVertice, int weight){
        this.weight = weight;
        this.connectedVertice = connectedVertice;
    }

    public int getConnectedVertice(){
        return this.connectedVertice;
    }

    public void setConnectedVertice(int connectedVertice) {
        this.connectedVertice = connectedVertice;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public String toString(){
        return weight + "->" + connectedVertice;
    }

}
