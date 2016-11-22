package fr.licinfo.drawer;

public class RectangleDrawerState implements DrawerState {

	double posX=-1;
	double posY=-1;
	
	public void mousePressed(DrawerContext context, double x, double y) {
		posX = x;
		posY = y;
	}

	public void mouseReleased(DrawerContext context, double x, double y) {
		context.drawer().add(new Rectangle(posX, posY, x - posX, y - posY));
		context.drawer().getGraphicsContext2D().clearRect(0, 0, context.drawer().getWidth(), context.drawer().getHeight());
		paint(context.drawer());
	}

	public void mouseMoved(DrawerContext context, double x, double y) {
		Drawer drawer = context.drawer();
		drawer.getGraphicsContext2D().clearRect(0, 0, drawer.getWidth(), drawer.getHeight());
		context.drawer().getGraphicsContext2D().strokeRect(posX, posY, x - posX, y - posY);
		paint(drawer);
		
	}

	public void paint(Drawer drawer) {
		drawer.repaint();
	}
	
	public boolean isInitialised() {
		return posX != -1;
	}
}
