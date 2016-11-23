package fr.licinfo;

/**
 * Created by sebastientosello on 23/11/2016.
 */
public class Edge {
    private int departureVertex, arrivalVertex, weight;

    public Edge(int departureVertex, int arrivalVertex, int weight){
        this.departureVertex = departureVertex;
        this.arrivalVertex = arrivalVertex;
        this.weight = weight;
    }

    public int getDepartureVertex() {
        return departureVertex;
    }

    public void setDepartureVertex(int departureVertex) {
        this.departureVertex = departureVertex;
    }

    public int getArrivalVertex() {
        return arrivalVertex;
    }

    public void setArrivalVertex(int arrivalVertex) {
        this.arrivalVertex = arrivalVertex;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public String toString(){
        return departureVertex + "-" + weight + "->" + arrivalVertex;
    }
}
