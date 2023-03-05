#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <signal.h>
#include <stdlib.h>
#include <X11/Xatom.h>

// screen size
#define WIDTH 1920
#define HEIGHT 1080

int n_rects = 1000;
int rect_w = WIDTH / 10;
int rect_h = HEIGHT / 10;

unsigned long black, white;
Display *display;
Window window;
int screen;
Atom wmDeleteMessage;

void draw_rects()
{
    for (int i = 0; i < n_rects; i++)
    {
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        int color = 0xff << 24 | r << 16 | g << 8 | b;

        int x = rand() % (WIDTH - rect_w);
        int y = rand() % (HEIGHT - rect_h);


        XSetForeground(display, DefaultGC(display, screen), color);
        XFillRectangle(display, window, DefaultGC(display, screen), x, y, rect_w, rect_h);
    }

    XSetForeground(display, DefaultGC(display, screen), 0xffffffff);
    XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, 300, 300);
}

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

void toggleFullscreen() {
    Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
    Atom wmFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent event = { 0 };
    event.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = wmState;
    event.xclient.format = 32;
    event.xclient.data.l[0] = 2; // _NET_WM_STATE_TOGGLE
    event.xclient.data.l[1] = wmFullscreen;
    event.xclient.data.l[2] = 0;

    XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask | SubstructureRedirectMask, &event);
}

int main() {
    signal(SIGINT, signalHandler);

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        exit(1);
    }
    screen = DefaultScreen(display);

    black = BlackPixel(display, screen);
    white = WhitePixel(display, screen);

    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, DisplayWidth(display, screen), DisplayHeight(display, screen), 0, black, white);
    XSelectInput(display, window, ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask);
    XMapWindow(display, window);

    XRRScreenResources *res = XRRGetScreenResources(display, RootWindow(display, screen));
    XRRCrtcInfo *crtcInfo = XRRGetCrtcInfo(display, res, res->crtcs[0]);
    XMoveResizeWindow(display, window, crtcInfo->x, crtcInfo->y, crtcInfo->width, crtcInfo->height);
    XRRFreeCrtcInfo(crtcInfo);
    XRRFreeScreenResources(res);

    Atom wmFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
    XChangeProperty(display, window, XInternAtom(display, "_NET_WM_STATE", False), XA_ATOM, 32, PropModeReplace, (unsigned char *)&wmFullscreen, 1);

    wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    toggleFullscreen();

    while (1) {
        XEvent event;
        XNextEvent(display, &event);
        switch (event.type) {
            case Expose:
                XSetForeground(display, DefaultGC(display, DefaultScreen(display)), black);
                XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, DisplayWidth(display, screen), DisplayHeight(display, screen));
                XFlush(display);
                break;
            case ButtonPress:
                if (event.xbutton.button == Button1) {
                    XSetForeground(display, DefaultGC(display, screen), black);
                    XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, DisplayWidth(display, screen), DisplayHeight(display, screen));
                    draw_rects();
                    XFlush(display);
                }
                break;
            case ButtonRelease:
                if (event.xbutton.button == Button1) {
                    XSetForeground(display, DefaultGC(display, DefaultScreen(display)), black);
                    XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, DisplayWidth(display, screen), DisplayHeight(display, screen));
                    XFlush(display);
                }
                break;
        }
    }

    XCloseDisplay(display);
    return 0;
}
