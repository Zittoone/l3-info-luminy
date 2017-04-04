package fr.licinfo;

import javax.swing.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

/**
 * Created by Alexis Couvreur on 16/12/2016.
 */
public class Scenario {
    public static void main(String[] args) {

        //Création des instances
        OpenPitInstance openPitInstance = null;
        JFrame window = new JFrame("visual");

        try {
            File f = new File("src/res/instances/instance400");
            openPitInstance = OpenPitInstance.readFromJsonFile(f.getAbsolutePath());
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }


        long time = System.currentTimeMillis();

        // Création d'un graphe de n élément + 2 (source, skin)
        Graph graph = new FlowGraph(openPitInstance.nbr_blocks + 2);

        // Map pour la création de la visualisation
        Map<Integer, OpenPitInstance.Block> map = new HashMap<>();

        // Liste des blocks à enlever (qui sont bloqués par un block non supprimable au dessus)
        List<Integer> removeChaine = new ArrayList<>();


        for (OpenPitInstance.Block block : openPitInstance.blocks){
            // On place le block dans la map
            map.put(block.uid, block);

            // La capacité
            double cap = openPitInstance.ore_value * block.ore - block.cost;
            // Si seulement le block est "removable" on traite le cas
            if(block.is_removable){
                if(cap > 0){
                    graph.addEdge(new Edge(graph.getSource(), block.uid, cap));
                } else {
                    graph.addEdge(new Edge(block.uid, graph.getSink(), Math.abs(cap)));
                }

                // Pour chacun des blocks au dessus
                for (Integer blockAbove : block.blocks_above){
                    // Si le block du dessus actuellement parcouru est "removable"
                    if(openPitInstance.blocks.get(openPitInstance.nbr_blocks - blockAbove - 1).is_removable){
                        graph.addEdge(new Edge(block.uid, blockAbove, Integer.MAX_VALUE));
                    } else {
                        removeChaine.add(block.uid);
                    }
                }
            }

        }

        // on enlève en chaine
        for (Integer vertex : removeChaine){
            removeEnChaine(graph, vertex);
        }


        System.out.println("Graph après parcous d'une instance de OpenPitInstance");
        System.out.println(graph.toString());
        System.out.println("\nValeur du flot max : " + GraphUtils.edmondsKarpMaxFlowValue(graph));

        //Graph cutminG = GraphUtils.minimalCut(graph);
        System.out.println("\nGraph après execution de la coupe minimale");
        //System.out.println(cutminG.toString());

        System.out.println("Temps d'execution :" + (System.currentTimeMillis() - time) + "ms");

        //System.out.println(cutminG.equals(graph));

        OpenPitVisualisation openPitVisualisation = new OpenPitVisualisation(map);
        openPitVisualisation.startVisual(window);

        List<Integer> integers = GraphUtils.minimalCut(graph);
        openPitVisualisation.setSolution(integers);

        openPitVisualisation.repaint();

    }

    // Spécifique au scénario et instances
    private static void removeEnChaine(Graph g, int node) {
        Queue<Integer> verticesToRemove = new LinkedList<Integer>();
        verticesToRemove.offer(node);
        while (!verticesToRemove.isEmpty()) {
            node = verticesToRemove.poll();
            if (node == g.getSink() || node == g.getSource())
                continue;
            System.out.println("Remove " + node);
            for (int i = 0; i < g.numNodes(); i++) {
                if (g.getEdge(i, node) != null){
                    g.removeEdge(g.getEdge(i, node));
                    verticesToRemove.add(i);
                }
                g.removeEdge(g.getEdge(node, i));
            }
        }
    }
}
