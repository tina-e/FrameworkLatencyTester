import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Random;

public class Java2D_rects extends JFrame {
    private Color color;
    private boolean pressed = false;

    public Java2D_rects() {
        setSize(1920, 1080);
        setTitle("Swing Test Application");
        setExtendedState(JFrame.MAXIMIZED_BOTH);
        setVisible(true);
        color = new Color(0, 0, 0);

        Graphics2D g2d = (Graphics2D) getGraphics();
        g2d.setColor(color);
        g2d.fillRect(0, 0, getWidth(), getHeight());
    }

    public void paint(Graphics g) {
        if(pressed)
        {
            //Graphics2D g2d = (Graphics2D) g;
            //Random r = new Random();
            //for (int i = 0; i < 1000; i++) {
            //    int x = r.nextInt(1920);
            //    int y = r.nextInt(1080);
            //    int width = r.nextInt(1920 - x);
            //    int height = r.nextInt(1080 - y);
            //    float red = r.nextInt(255);
            //    float green = r.nextFloat();
            //    float blue = r.nextFloat();
            //    float alpha = 255; //r.nextFloat();
            //    g2d.setColor(new Color(red, green, blue, alpha));
            //    g2d.fillRect(x, y, width, height);
            //}
            //g2d.setColor(new Color(255.0f, 255.0f, 255.0f, 255.0f));
            //g2d.fillRect(0, 0, 300, 300);
            //pressed = false;
        }
    }

    public void mousePressed(MouseEvent e) {
        color = new Color(255, 255, 255);
        Graphics2D g2d = (Graphics2D) getGraphics();

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
            g2d.setColor(new Color(red, green, blue));
            g2d.fillRect(x, y, width, height);
        }
        g2d.setColor(new Color(255, 255, 255));
        g2d.fillRect(0, 0, 300, 300);

        //g2d.setColor(color);
        //g2d.fillRect(0, 0, getWidth(), getHeight());
        //pressed = true;
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
        Java2D_rects window = new Java2D_rects();
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
