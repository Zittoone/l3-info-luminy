package fr.licinfo.drawer;

public class MoveDrawerState implements DrawerState{

	Shape shape;
	private double posX;
	private double posY;
	
	public void mousePressed(DrawerContext context, double x, double y) {
		shape = context.drawer().shapesContaining(x, y);
		posX = x;
		posY = y;
		
	}

	public void mouseReleased(DrawerContext context, double x, double y) {
		return;
		
	}

	public void mouseMoved(DrawerContext context, double x, double y) {
		if (isInitialised()) {
			shape.translate(x - posX, y - posY);
			posX = x;
			posY = y;
			context.drawer().getGraphicsContext2D().clearRect(0, 0, context.drawer().getWidth(), context.drawer().getHeight());
			context.drawer().repaint();
		}
		
	}

	public void paint(Drawer drawer) {
		if (isInitialised())
			shape.paint(drawer.getGraphicsContext2D());
		
	}

	public boolean isInitialised() {
		return shape != null;
	}

}
