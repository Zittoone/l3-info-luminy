package fr.licinfo;

/**
 * Created by sebastientosello on 04/10/2016.
 */
public class HtmlFormat implements ListFormat {
    public String listStart() {
        return "<ul>";
    }

    public String listEnd() {
        return "</ul>";
    }

    public String itemStart() {
        return "<li>";
    }

    public String itemEnd() {
        return "</li>";
    }
}
