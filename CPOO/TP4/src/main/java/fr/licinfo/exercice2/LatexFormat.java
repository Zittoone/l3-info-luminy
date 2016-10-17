package fr.licinfo.exercice2;

import fr.licinfo.exercice2.ListFormat;

/**
 * Created by c16017548 on 11/10/16.
 */
public class LatexFormat implements ListFormat {
    public String listStart() {
        return "\\begin{itemize}\n";
    }

    public String listEnd() {
        return "\\end{itemize}\n";
    }

    public String itemStart() {
        return "\\item ";
    }

    public String itemEnd() {
        return "\n";
    }
}
