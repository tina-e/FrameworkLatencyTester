import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class JavaSwing_image extends JFrame {
    private Color color;
    private Image image;
    private boolean pressed = false;

    public JavaSwing_image() {
        setSize(1920, 1080);
        setTitle("Swing Test Application");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        color = new Color(0, 0, 0);
        image = Toolkit.getDefaultToolkit().getImage("noise.png");
    }

    public void paint(Graphics g) {
        if (pressed)
        {
            g.drawImage(image, 0, 0, this);
        }
        else
        {
            g.setColor(color);
            g.fillRect(0, 0, getWidth(), getHeight());
        }
    }

    public void mousePressed(MouseEvent e) {
        pressed = true;
        Graphics g = getGraphics();
        if (g != null) {
            g.drawImage(image, 0, 0, this);
            Toolkit.getDefaultToolkit().sync();
        }
    }

    public void mouseReleased(MouseEvent e) {
        pressed = false;
        color = new Color(0, 0, 0);

        Graphics g = getGraphics();
        if (g != null) {
            g.setColor(color);
            g.fillRect(0, 0, getWidth(), getHeight());
            Toolkit.getDefaultToolkit().sync();
        }
    }

    public static void main(String[] args) {
        JavaSwing_image window = new JavaSwing_image();
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
