import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Java2D extends JFrame {
    private Color color;

    public Java2D() {
        setSize(1920, 1080);
        setTitle("Swing Test Application");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setUndecorated(true);
        setVisible(true);
        color = new Color(0, 0, 0);
    }

    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        g2d.setColor(color);
        g2d.fillRect(0, 0, getWidth(), getHeight());
    }

    public void mousePressed(MouseEvent e) {
        color = new Color(255, 255, 255);

        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(color);
               g2d.fillRect(0, 0, getWidth(), getHeight());
	Toolkit.getDefaultToolkit().sync();
    }

    public void mouseReleased(MouseEvent e) {
        color = new Color(0, 0, 0);

        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(color);
               g2d.fillRect(0, 0, getWidth(), getHeight());
	Toolkit.getDefaultToolkit().sync();
    }

    public static void main(String[] args) {
        Java2D window = new Java2D();
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
