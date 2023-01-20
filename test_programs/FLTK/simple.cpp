// this code was translated from the PyQt5 application using Chat-GPT

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

class MainWindow : public Fl_Double_Window
{
    public:
        MainWindow() : Fl_Double_Window(0, 0, 1920, 1080)
    {
        color(FL_BLACK);
        label("FLTK Test Application");
        fullscreen();
    }

    protected:
        void draw() override
        {
            fl_color(color());
            fl_rectf(0, 0, w(), h());
        }

        int handle(int event) override
        {
            switch (event)
            {
                case FL_PUSH:
                    color(FL_WHITE);
                    redraw();
                    return 1;
                case FL_RELEASE:
                    color(FL_BLACK);
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
