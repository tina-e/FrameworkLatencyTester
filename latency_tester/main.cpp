#include <stdio.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <X11/Xutil.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#include <linux/input.h>

#define WIDTH 1
#define HEIGHT 1
#define X 200
#define Y 200
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0xFF000000
#define MOUSE_BUTTON_LEFT 272
#define CLICKED 1
#define EVENT_TYPE_CLICK_EVDEV 0
#define EVENT_TYPE_XSHM 1

using namespace std;

const char* EVENT_NAMES[2] = {"click_evdev", "xshm"};

Display *display;
Window rootWindow;
XShmSegmentInfo shminfo;
XImage *image;

char* program_under_test;

struct Event {
    uint64_t time;
    int iteration;
    int event_type;
};

vector<Event> events;

void logEvent(uint64_t time, int event, int iteration)
{
    Event tempEvent = Event();
    tempEvent.time = time;
    tempEvent.event_type = event;
    tempEvent.iteration = iteration;
    events.push_back(tempEvent);
}

void printLog()
{
    cout << "time,iteration,event,program" << endl;
    for(auto const& ev : events) {
        cout << dec << ev.time << "," << ev.iteration << "," << EVENT_NAMES[ev.event_type] << "," << program_under_test << endl;
    }
}

uint64_t micros()
{
    using namespace chrono;
    uint64_t us = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
    return us; 
}

void initXShm()
{
    XWindowAttributes windowAttributes;
    Screen *screen;

    display = XOpenDisplay(getenv("DISPLAY"));
    rootWindow = DefaultRootWindow(display);
    XGetWindowAttributes(display, rootWindow, &windowAttributes);
    screen = windowAttributes.screen;

    image = XShmCreateImage(display, DefaultVisualOfScreen(screen), DefaultDepthOfScreen(screen), ZPixmap, NULL, &shminfo, WIDTH, HEIGHT);

    shminfo.shmid = shmget(IPC_PRIVATE, image->bytes_per_line * image->height, IPC_CREAT|0777);
    shminfo.shmaddr = image->data = (char*)shmat(shminfo.shmid, 0, 0);
    shminfo.readOnly = False;
    XShmAttach(display, &shminfo);
}

void closeXShm()
{
    XShmDetach(display, &shminfo);
    XDestroyImage(image);
}

unsigned int getPixelColor()
{
    XShmGetImage(display, rootWindow, image, X, Y, 0x00ffffff);
    return image->data[2]; // red
}

void wait_for_color(unsigned int color)
{
    while(getPixelColor() != color)
    {
        usleep(1);
    }
    return;
}

void cleanup()
{
    closeXShm();
}

void signalHandler(int sig)
{
    printLog();
    cleanup();
    exit(sig);
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandler);

    int input_fd = -1;
    struct input_event inputEvent;
    int err = -1;
    char* event_handle;

    if(argc < 3)
    {
        cerr << "Too few arguments!" << endl
             << "Usage: latency_tester INPUT_DEVICE PROGRAM_NAME" << endl
             << "INPUT_DEVICE: path to /dev/input/eventXY" << endl
             << "PROGRAM_NAME: name of program under test to appear in log files" << endl;
        exit(SIGABRT);
    }
    else
    {
        event_handle = argv[1];
        program_under_test = argv[2];
    }

    input_fd = open(event_handle, O_RDONLY | O_NONBLOCK);

    if(input_fd == -1)
    {
        cerr << "Could not open input device " << event_handle << endl;
        exit(SIGABRT);
    }

    int iteration = 0;

    initXShm();

    while(true)
    {
        err = read(input_fd, &inputEvent, sizeof(struct input_event));
        if(err > -1 && inputEvent.type == EV_KEY)
        {
            if(inputEvent.code == MOUSE_BUTTON_LEFT && inputEvent.value == CLICKED)
            {
                logEvent(micros(), EVENT_TYPE_CLICK_EVDEV, iteration);
                wait_for_color(COLOR_WHITE);
                logEvent(micros(), EVENT_TYPE_XSHM, iteration);
                iteration++;
            }
        }
    }

    printLog();
    cleanup();

    return 0;
}
