#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class MainWindow : public QWidget
{
    public:
        MainWindow(QWidget *parent = 0);

    protected:
        void paintEvent(QPaintEvent *e);
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);

    private:
        void paint();
        void click();
        void release();
        QBrush brush;
        QImage img;
        int pressed = false;
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    brush = QBrush("#000000");
    img = QImage("noise.png");
    repaint();
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        click();
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        release();
        repaint();
    }
}

void MainWindow::click()
{
    pressed = 1;
}

void MainWindow::release()
{
    pressed = 0;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    paint();
}

void MainWindow::paint()
{
    QPainter painter(this);
    painter.setBrush(brush);   

    if (pressed)
    {
        painter.drawImage(QRect(0, 0, 1920, 1080), img);
    }
    else
    {
        painter.drawRect(0, 0, 1920, 1080);
    }
    //QGuiApplication::sync();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;

    window.setGeometry(0, 0, 1920, 1080);
    window.setWindowTitle("Qt5 Test Application");
    window.showFullScreen();
    window.show();

    return app.exec();
}
