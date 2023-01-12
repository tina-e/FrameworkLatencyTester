import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Color;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.*;

public class JavaSwing implements MouseListener {

    JFrame frame;

    public JavaSwing() {
        GraphicsEnvironment graphics = GraphicsEnvironment.getLocalGraphicsEnvironment();
        GraphicsDevice device = graphics.getDefaultScreenDevice();
        frame = new JFrame("Fullscreen");
        device.setFullScreenWindow(frame);


        frame.getContentPane().setBackground(Color.BLACK);
        frame.addMouseListener(this);

    }

    public static void main(String[] args) {
        new JavaSwing();
    }


    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        frame.getContentPane().setBackground(Color.WHITE);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        frame.getContentPane().setBackground(Color.BLACK);
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}