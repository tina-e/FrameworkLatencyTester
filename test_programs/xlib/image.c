#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <signal.h>
#include <stdlib.h>
#include <X11/Xatom.h>
#include <png.h>

#define WIDTH 1920
#define HEIGHT 1080

// make sure we clean up when program is interrupted
void signalHandler(int sig)
{
    exit(sig);
}

unsigned long black, white;
Display *display;
Window window;
int screen;
Atom wmDeleteMessage;
int pressed = 0;
XImage* img;
Pixmap pixmap;

void read_png_file(char* file_name, unsigned char** image_data)
{
    png_byte header[8];

    FILE *fp = fopen(file_name, "rb");
    fread(header, 1, 8, fp);

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);

    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);

    png_read_info(png_ptr, info_ptr);

    int width_ = png_get_image_width(png_ptr, info_ptr);
    int height_ = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    if (bit_depth == 16)
        png_set_strip_16(png_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);


    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    printf("%d %d %d\n", color_type, bit_depth, rowbytes);
    *image_data = (unsigned char*) malloc(rowbytes * HEIGHT);
    png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * HEIGHT);
    for (int y = 0; y < HEIGHT; y++)
        row_pointers[y] = *image_data + y * rowbytes;

    png_read_image(png_ptr, row_pointers);

    fclose(fp);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    free(row_pointers);
}

void redraw() {
    if (pressed)
    {
        XPutImage(display, window, DefaultGC(display, 0), img, 0, 0, 0, 0, WIDTH, HEIGHT);
    }
    else
    {
        XFillRectangle(display, window, DefaultGC(display, screen), 0, 0, DisplayWidth(display, screen), DisplayHeight(display, screen));
    }
    XFlush(display);
}

void toggleFullscreen() {
    // Plasma
    Atom wmState = XInternAtom(display, "_NET_WM_STATE", True);
    Atom wmFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", True);

    Atom wm_state   = XInternAtom (display, "_NET_WM_STATE", True );
    Atom wm_fullscreen = XInternAtom (display, "_NET_WM_STATE_FULLSCREEN", True );

    XChangeProperty(display, window, wm_state, XA_ATOM, 32,
		    PropModeReplace, (unsigned char *)&wm_fullscreen, 1);

    // Xfce
    //Atom wmState = XInternAtom(display, "_NET_WM_STATE", False);
    //Atom wmFullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    //XEvent event = { 0 };
    //event.type = ClientMessage;
    //event.xclient.window = window;
    //event.xclient.message_type = wmState;
    //event.xclient.format = 32;
    //event.xclient.data.l[0] = 2; // _NET_WM_STATE_TOGGLE
    //event.xclient.data.l[1] = wmFullscreen;
    //event.xclient.data.l[2] = 0;

    //XSendEvent(display, DefaultRootWindow(display), False, SubstructureNotifyMask | SubstructureRedirectMask, &event);
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

    pixmap = XCreatePixmap(display, DefaultRootWindow(display), WIDTH, HEIGHT, DefaultDepth(display, DefaultScreen(display)));

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

    unsigned char* pixels;
    read_png_file("noise.png", &pixels);

    img = XCreateImage(display, DefaultVisual(display, 0), 24, ZPixmap, 0, (char*) pixels, 1920, 1080, 32, 7680);

    while (1) {
        XEvent event;
        XNextEvent(display, &event);
        switch (event.type) {
            case Expose:
                redraw();
                break;
            case ButtonPress:
                if (event.xbutton.button == Button1) {
                    pressed = 1;
                    redraw();
                }
                break;
            case ButtonRelease:
                if (event.xbutton.button == Button1) {
                    pressed = 0;
                    redraw();
                }
                break;
        }
    }

    XCloseDisplay(display);
    return 0;
}
