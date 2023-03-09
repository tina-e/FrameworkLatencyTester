// this code was translated from the PyQt5 application using Chat-GPT

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

class MainWindow : public Fl_Double_Window
{
    public:
        MainWindow() : Fl_Double_Window(0, 0, 1920, 1080)
    {
        color(FL_BLACK);
        fl_color(color());
        label("FLTK Test Application");
        fullscreen();
        image = new Fl_PNG_Image("noise.png");
    }

    private:
        int pressed = 0;
        Fl_PNG_Image *image;

    protected:
        void draw() override
        {
            if (pressed)
            {
                image->draw(0, 0, 1920, 1080);
            }
            else
            {
                fl_rectf(0, 0, w(), h());
            }
        }

        int handle(int event) override
        {
            switch (event)
            {
                case FL_PUSH:
                    pressed = 1;
                    redraw();
                    return 1;
                case FL_RELEASE:
                    pressed = 0;
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
