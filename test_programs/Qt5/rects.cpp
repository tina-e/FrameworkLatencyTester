#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>

int randint(int low, int high)
{
    return low + std::rand() % (high - low);
}

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
        bool active;
        void drawRects(QPainter *painter);
};

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    brush = QBrush("#000000");
    active = false;
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
    active = true;
    brush = QBrush("#FFFFFF");
}

void MainWindow::release()
{
    active = false;
    brush = QBrush("#000000");
}

void MainWindow::drawRects(QPainter *painter)
{
    for(int i = 0; i < 1000; i++)
    {
        int w = randint(100, 500);
        int h = randint(100, 500);
        int x = randint(0, 1920 - w);
        int y = randint(0, 1080 - h);
        int r = randint(0, 255);
        int g = randint(0, 255);
        int b = randint(0, 255);
        brush = QBrush(QColor(r, g, b));
        painter->setBrush(brush);    
        painter->drawRect(x, y, w, h);
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    paint();
}

void MainWindow::paint()
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);    

    if(active)
    {
        drawRects(&painter);
        brush = QBrush("#FFFFFF");
        painter.setBrush(brush);    
        painter.drawRect(0, 0, 300, 300);
    }
    else
    {
        painter.setBrush(brush);    
        painter.drawRect(0, 0, 1920, 1080);
    }
}

int main(int argc, char *argv[])
{
    std::srand(std::time(nullptr)); 
    QApplication app(argc, argv);

    MainWindow window;

    window.setGeometry(0, 0, 1920, 1080);
    window.setWindowTitle("Qt5 Test Application");
    window.showFullScreen();
    window.show();

    return app.exec();
}
