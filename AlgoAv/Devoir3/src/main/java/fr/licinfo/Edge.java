package fr.licinfo;

/**
 * Created by sebastientosello on 23/11/2016.
 */
public class Edge {
    private int cap, flow, dest, source ;

    public Edge(int source, int dest, int cap, int flow){
        this.source = source;
        this.dest = dest;
        this.cap = cap;
        this.flow = flow;
    }

    public Edge(int source, int dest, int flow){
        this.source = source;
        this.dest = dest;
        this.flow = flow;
    }

    public Edge(Edge e){
        this.source = e.getSource();
        this.dest = e.getDest();
        this.cap = e.getCap();
        this.flow = e.getFlow();
    }

    public int getCap() {
        return cap;
    }

    public int getFlow() {
        return flow;
    }

    public int getDest() {
        return dest;
    }

    public int getSource() {
        return source;
    }

    public void setCap(int cap) {
        this.cap = cap;
    }

    public void setFlow(int flow) {
        this.flow = flow;
    }

    @Override
    public String toString(){
        return dest + "--" + flow + "/" + cap + "-->" + dest;
    }

    @Override
    public boolean equals(Object o){
        if (this == o) {
            return true;
        }

        if (!(o instanceof Edge)){
            return false;
        }

        if(((Edge) o).getCap() != this.getCap()){
            return false;
        }

        if(((Edge) o).getDest() != this.getDest()){
            return false;
        }

        if(((Edge) o).getFlow() != this.getFlow()){
            return false;
        }

        if(((Edge) o).getSource() != this.getSource()){
            return false;
        }

        return true;
    }
}
