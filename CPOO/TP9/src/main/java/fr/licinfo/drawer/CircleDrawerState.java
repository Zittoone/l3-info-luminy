package fr.licinfo.drawer;

public class CircleDrawerState implements DrawerState{

	double posX=-1;
	double posY=-1;
	
	public void mousePressed(DrawerContext context, double x, double y) {
		posX = x;
		posY = y;
		
	}

	public void mouseReleased(DrawerContext context, double x, double y) {
		double radius = x - posX;
		context.drawer().add(new Circle(posX-radius/2, posY-radius/2, radius));
		context.drawer().getGraphicsContext2D().clearRect(0, 0, context.drawer().getWidth(), context.drawer().getHeight());
		paint(context.drawer());
		
	}

	public void mouseMoved(DrawerContext context, double x, double y) {
		double radius = x - posX;
		Drawer drawer = context.drawer();
		drawer.getGraphicsContext2D().clearRect(0, 0, drawer.getWidth(), drawer.getHeight());
		drawer.getGraphicsContext2D().strokeOval(posX-radius/2, posY-radius/2, radius, radius);
		paint(drawer);
	}

	public void paint(Drawer drawer) {
		drawer.repaint();
	}
	
	public boolean isInitialised() {
		return posX != -1;
	}

}
