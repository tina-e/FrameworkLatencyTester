import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class JavaSwing_rects extends JFrame {
    private Color color;

    public JavaSwing_rects() {
        setSize(1920, 1080);
        setTitle("Swing Test Application");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        color = new Color(0, 0, 0);
    }

    public void paint(Graphics g) {
	    g.setColor(color);
	    g.fillRect(0, 0, getWidth(), getHeight());
    }

    public void mousePressed(MouseEvent e) {
        color = new Color(255, 255, 255);


        Graphics g = getGraphics();

        Random r = new Random();
        for (int i = 0; i < 1000; i++) {
            int x = r.nextInt(1920);
            int y = r.nextInt(1080);
            int width = r.nextInt(1920 - x);
            int height = r.nextInt(1080 - y);
            int red = r.nextInt(254);
            int green = r.nextInt(255);
            int blue = r.nextInt(255);
            float alpha = 255; //r.nextFloat();
            g.setColor(new Color(red, green, blue));
            g.fillRect(x, y, width, height);
        }
        g.setColor(new Color(255, 255, 255));
        g.fillRect(0, 0, 300, 300);

        Toolkit.getDefaultToolkit().sync();
    }

    public void mouseReleased(MouseEvent e) {
        color = new Color(0, 0, 0);

        Graphics g = getGraphics();
        if (g != null) {
            g.setColor(color);
            g.fillRect(0, 0, getWidth(), getHeight());
            Toolkit.getDefaultToolkit().sync();
        }
    }

    public static void main(String[] args) {
        JavaSwing_rects window = new JavaSwing_rects();
        window.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                window.mousePressed(e);
            }

            public void mouseReleased(MouseEvent e) {
                window.mouseReleased(e);
            }
        });
        GraphicsEnvironment graphics = GraphicsEnvironment.getLocalGraphicsEnvironment();
        GraphicsDevice device = graphics.getDefaultScreenDevice();
        device.setFullScreenWindow(window);
    }
}
