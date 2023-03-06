import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Java2D_image extends JFrame {
    private Color color;
    private Image image;
    private boolean pressed = false;

    public Java2D_image() {
        setSize(1920, 1080);
        setTitle("Swing Test Application");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        color = new Color(0, 0, 0);
        image = Toolkit.getDefaultToolkit().getImage("noise.png");
    }

    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D) getGraphics();
        if (pressed)
        {
            g2d.drawImage(image, 0, 0, null);
        }
        else
        {
            g2d.setColor(color);
            g2d.fillRect(0, 0, getWidth(), getHeight());
        }
    }

    public void mousePressed(MouseEvent e) {
        pressed = true;
        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.drawImage(image, 0, 0, null);
        Toolkit.getDefaultToolkit().sync();
    }

    public void mouseReleased(MouseEvent e) {
        pressed = false;
        color = new Color(0, 0, 0);

        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(color);
        g2d.fillRect(0, 0, getWidth(), getHeight());
        Toolkit.getDefaultToolkit().sync();
    }

    public static void main(String[] args) {
        Java2D_image window = new Java2D_image();
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
