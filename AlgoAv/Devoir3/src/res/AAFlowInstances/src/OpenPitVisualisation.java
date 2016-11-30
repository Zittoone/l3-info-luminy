import javax.swing.*;
import java.awt.*;
import java.awt.geom.Path2D;
import java.awt.geom.Point2D;
import java.util.Collection;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

/**
 * Created by guyslain on 15/11/16.
 */
public class OpenPitVisualisation extends JPanel {
  private static final long serialVersionUID = 1132559075369872L;

  private final static int panelWidth = 1800;
  private final static int panelHeight = 800;

  private final static Stroke strokeBorder = new BasicStroke(1);

  private final Map<Integer,OpenPitInstance.Block> instance;
  private Set<Integer> minCut;
  private final double maxDensity;
  private final double minDensity;

  public OpenPitVisualisation(Map<Integer,OpenPitInstance.Block> instance) {
    this.instance = instance;
    this.minCut = new TreeSet<>();
    this.maxDensity =
      instance.values().stream()
        .map(OpenPitInstance.Block::getDensity)
        .max(Double::compareTo)
        .orElse(1.);
    this.minDensity =
      instance.values().stream()
        .map(OpenPitInstance.Block::getDensity)
        .min(Double::compareTo)
        .orElse(0.);
    setPreferredSize(new Dimension(panelWidth, panelHeight));
  }

  public void setSolution(Collection<Integer> minCut) {
    this.minCut = new TreeSet<>();
    for (Integer blockId : minCut)
      this.minCut.add(blockId);
  }

  public void addBlockToSolution(int blockId) {
    if (this.minCut == null) this.minCut = new TreeSet<>();
    this.minCut.add(blockId);
  }


  public void startVisual(JFrame window) {
    window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    window.getContentPane().add(this);
    window.pack();
    window.setLocationRelativeTo(null);
    window.setVisible(true);
    SwingUtilities.invokeLater(() -> this.repaint());
  }




  private Point2D toPoint(OpenPitInstance.Point point) {
    return new Point2D.Double(point.x, 800. - point.y);
  }

  private Shape shapeOfBlock(OpenPitInstance.Block block) {
    Path2D.Double polygon = new Path2D.Double();
    Point2D vertex = toPoint(block.polygon.get(0));
    polygon.moveTo(vertex.getX(), vertex.getY());
    for (int i = 1; i < block.polygon.size(); i++) {
      vertex = toPoint(block.polygon.get(i));
      polygon.lineTo(vertex.getX(),vertex.getY());
    }
    polygon.closePath();
    return polygon;
  }

  private Color colorOfBlock(OpenPitInstance.Block block, boolean removed) {
    float brightness = (float)
      (0.75 * (block.getDensity() - minDensity) / (maxDensity - minDensity)
        + 0.25);
    float hue = 0;
    if (removed) hue = (float) 0.35;
    return Color.getHSBColor(hue, (float) 0.75, brightness);
  }


  private void drawBlock(Graphics2D gr,
                         OpenPitInstance.Block block,
                         boolean removed) {
    Shape polygon = shapeOfBlock(block);
    Color color = colorOfBlock(block,removed);
    gr.setColor(color);
    gr.fill(polygon);
    gr.setColor(Color.WHITE);
    gr.setStroke(strokeBorder);
    gr.draw(polygon);
  }

  private void renderSolution(Graphics2D gr) {
    for(Map.Entry<Integer,OpenPitInstance.Block> entry : instance.entrySet()) {
      boolean removed = minCut.contains(entry.getKey());
      drawBlock(gr, entry.getValue(), removed);
    }
  }

  private void drawBackground(Graphics2D graphics) {
    super.setBackground(Color.WHITE);
    super.paintComponent(graphics);
  }

  public void paintComponent(Graphics graphics) {
    Graphics2D gr = (Graphics2D) graphics;
    RenderingHints rh =
      new RenderingHints(
        RenderingHints.KEY_ANTIALIASING,
        RenderingHints.VALUE_ANTIALIAS_ON
      );
    gr.setRenderingHints(rh);
    drawBackground(gr);
    renderSolution(gr);
  }

}
