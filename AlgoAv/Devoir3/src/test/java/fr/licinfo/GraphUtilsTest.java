package fr.licinfo;

import org.junit.Before;
import org.junit.Test;

import static org.hamcrest.core.IsEqual.equalTo;
import static org.junit.Assert.assertThat;

/**
 * Created by Alexis Couvreur on 18/12/2016.
 */
public class GraphUtilsTest {

    Graph graph;

    @Before
    public void setUp() throws Exception {
        graph = new FlowGraph(7);

        graph.addEdge(new Edge(0, 1, 4.2));
        graph.addEdge(new Edge(1, 4, 3.2));
        graph.addEdge(new Edge(1, 5, 1.2));
        graph.addEdge(new Edge(4, 5, 2.2));
        graph.addEdge(new Edge(0, 2, 2.2));
        graph.addEdge(new Edge(2, 3, 2.2));
        graph.addEdge(new Edge(2, 4, 0.2));
        graph.addEdge(new Edge(5, 6, 4.2));
        graph.addEdge(new Edge(3, 6, 2.2));
    }

    @Test
    public void edmondsKarpMaxFlowValue() throws Exception {

        assertThat(GraphUtils.edmondsKarpMaxFlowValue(graph), equalTo(4.2));
    }

}