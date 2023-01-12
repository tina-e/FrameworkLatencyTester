import java.awt.Frame;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Color;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class JavaAWT implements MouseListener {

    Frame frame;

    public JavaAWT() {
        GraphicsEnvironment graphics = GraphicsEnvironment.getLocalGraphicsEnvironment();
        GraphicsDevice device = graphics.getDefaultScreenDevice();

        frame = new Frame();
        frame.setBackground(Color.BLACK);
        frame.addMouseListener(this);

        device.setFullScreenWindow(frame);

    }

    public static void main(String[] args) {
        new JavaAWT();
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        frame.setBackground(Color.WHITE);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        frame.setBackground(Color.BLACK);
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}
