package fr.licinfo;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by c16017548 on 04/10/16.
 */
public class ItemList {
    private List<String> items;

    public ItemList() { items = new ArrayList<String>(); }

    public void add(String item) { items.add(item); }

    public void printHTML() {
        System.out.print("<ul>");
        for (String i : items) System.out.print("<li>"+i+"</li>");
        System.out.print("</ul>");
    }

    public void printLaTeX() {
        System.out.println("\\begin{itemize}");
        for (String i : items) System.out.println("\\item "+i);
        System.out.println("\\end{itemize}");
    }
}