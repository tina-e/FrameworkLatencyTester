#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <cstdlib>

class MainWindow : public Fl_Double_Window
{
    public:
        MainWindow() : Fl_Double_Window(0, 0, 1920, 1080)
    {
        color(FL_BLACK);
        label("FLTK Test Application");
        fullscreen();
    }
        bool pressed = false;

    protected:
        void draw() override
        {
            if(pressed)
            {
                fl_color(color());
                fl_rectf(0, 0, w(), h());
                for (int i = 0; i < 1000; i++)
                {
                    float r = rand() % 255;
                    float g = rand() % 255;
                    float b = rand() % 255;
                    float a = rand() % 255;
                    fl_color(r, g, b);

                    int x = rand() % (w() - 300);
                    int y = rand() % (h() - 300);
                    int width = rand() % (w() - x);
                    int height = rand() % (h() - y);

                    fl_rectf(x, y, width, height);
                }
                fl_color(FL_WHITE);
                fl_rectf(0, 0, 300, 300);
            }
            else
            {
                fl_color(FL_BLACK);
                fl_rectf(0, 0, w(), h());
            }
        }

        int handle(int event) override
        {
            switch (event)
            {
                case FL_PUSH:
                    pressed = true;
                    redraw();
                    return 1;
                case FL_RELEASE:
                    pressed = false;
                    redraw();
                    return 1;
            }
            return Fl_Double_Window::handle(event);
        }
};

int main(int argc, char **argv)
{
    MainWindow window;
    window.show();
    return Fl::run();
}
