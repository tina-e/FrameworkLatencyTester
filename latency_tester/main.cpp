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

using namespace std;

// position and dimension (should only one pixel!) of the region observed by XShm
#define WIDTH 1
#define HEIGHT 1
int X = 200;
int Y = 200;

// colors used by the test program
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_BLACK 0xFF000000

// input event
#define MOUSE_BUTTON_LEFT 272
#define CLICKED 1

// variables for xshm
Display *display;
Window rootWindow;
XShmSegmentInfo shminfo;
XImage *image;

char* testProgramName;

// as printing to stdout is slow, we store all events occuring in a list
// and print its content in the end
#define EVENT_TYPE_CLICK_EVDEV 0
#define EVENT_TYPE_XSHM 1

struct Event {
    uint64_t time;  // event timestamp in microseconds
    int iteration;  // iteration number to identify events belonging together
    int event_type; // used to identify events; replaced with EVENT_NAMES when printing the log
};

vector<Event> events;   // event list

// used to make events human readable for easier evaluation
const char* EVENT_NAMES[2] = {"click_evdev", "xshm"};

// appends event to the events list
void logEvent(uint64_t time, int event, int iteration)
{
    Event tempEvent = Event();
    tempEvent.time = time;
    tempEvent.event_type = event;
    tempEvent.iteration = iteration;
    events.push_back(tempEvent);
}

// called when program is finished
// iterates the events list and prints it to stdout in CSV format
void printLog()
{
    cout << "time,iteration,event,program" << endl;
    for(auto const& ev : events)
    {
        cout << dec <<
            ev.time << "," <<
            ev.iteration << "," <<
            EVENT_NAMES[ev.event_type] << "," <<
            testProgramName << endl;
    }
}

// get current microseconds
uint64_t micros()
{
    using namespace chrono;
    //return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
    return duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count();
}

// initialize the XShm extension to be able to read one pixel from the screen
void initXShm()
{
    XWindowAttributes windowAttributes;
    Screen *screen;

    display = XOpenDisplay(getenv("DISPLAY"));
    rootWindow = DefaultRootWindow(display);
    XGetWindowAttributes(display, rootWindow, &windowAttributes);
    screen = windowAttributes.screen;

    // create an image object that will store the pixel data
    image = XShmCreateImage(display, DefaultVisualOfScreen(screen), DefaultDepthOfScreen(screen), ZPixmap, NULL, &shminfo, WIDTH, HEIGHT);

    shminfo.shmid = shmget(IPC_PRIVATE, image->bytes_per_line * image->height, IPC_CREAT|0777);
    shminfo.shmaddr = image->data = (char*)shmat(shminfo.shmid, 0, 0);
    shminfo.readOnly = False;
    XShmAttach(display, &shminfo);
}

// detach XShm and clean up memory
// this has to be called when the program terminates
void closeXShm()
{
    XShmDetach(display, &shminfo);
    XDestroyImage(image);
}

// get pixel at specified position with XShm
unsigned int getPixelColor()
{
    XShmGetImage(display, rootWindow, image, X, Y, 0x00ffffff);
    return image->data[2]; // red channel is enough for us
}

unsigned int getPixelColorX()
{
    XColor c;
    XImage *image;

    image = XGetImage (display, rootWindow, X, Y, 1, 1, AllPlanes, XYPixmap);

    c.pixel = XGetPixel (image, 0, 0);

    XFree (image);

    XQueryColor (display, XDefaultColormap(display, XDefaultScreen (display)), &c);

    //cout << c.red/256 << " " << c.green/256 << " " << c.blue/256 << "\n";
    //cout << c.red / 256 << endl;

    return c.red / 256;
}

// wait until our pixel has a specified color
void wait_for_color(unsigned int color)
{
    //cout << getPixelColorX() << " " << color << endl;
    while(getPixelColor() != color)
    //while(getPixelColorX() != color)
    {
        usleep(1);
    }
    return;
}

// do all the cleanup before terminating
void cleanup()
{
    closeXShm();
}

// make sure we clean up and print current logs when the program is killed
// log is only printed when terminated, not when interrupted
void signalHandlerInt(int sig)
{
    //printLog();
    cleanup();
    exit(sig);
}

void signalHandlerTerm(int sig)
{
    //printLog();
    cleanup();
    exit(sig);
}

int main(int argc, char** argv)
{
    signal(SIGINT, signalHandlerInt);
    signal(SIGTERM, signalHandlerTerm);

    // variables used by evdev to get input events
    int input_fd = -1;
    struct input_event inputEvent;
    int err = -1;
    char* event_handle; // path to /dev/input/eventXY for the used input device

    // check command line parameters
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
        testProgramName = argv[2];
    }

    if(argc == 5)
    {
        X = atoi(argv[3]);
        Y = atoi(argv[4]);
    }

    int iteration = 0;

    initXShm();

    //while(true)
    //{
    //        logEvent(micros(), EVENT_TYPE_CLICK_EVDEV, iteration); // log input event timestamp
    //        wait_for_color(COLOR_WHITE); // wait for test program to react
    //        logEvent(micros(), EVENT_TYPE_XSHM, iteration); // log color change timestamp
    //        iteration++;
    //}

    // open input device
    input_fd = open(event_handle, O_RDONLY | O_NONBLOCK);

    if(input_fd == -1)
    {
        cerr << "Could not open input device " << event_handle << endl;
        exit(SIGABRT);
    }

    uint64_t start_time = micros();
    uint64_t end_time = micros();

    while(true)
    {
        // read input events from the specified device
        err = read(input_fd, &inputEvent, sizeof(struct input_event));

        // detected a left mouse click
        if( err > -1 &&
            inputEvent.type == EV_KEY &&
            inputEvent.code == MOUSE_BUTTON_LEFT &&
            inputEvent.value == CLICKED)
        {
            start_time = micros();
            //logEvent(micros(), EVENT_TYPE_CLICK_EVDEV, iteration); // log input event timestamp
            wait_for_color(COLOR_WHITE); // wait for test program to react
            //wait_for_color(255); // wait for test program to react

            //logEvent(micros(), EVENT_TYPE_XSHM, iteration); // log color change timestamp
            end_time = micros();

            cout << end_time - start_time << endl;
            iteration++;
        }

        // does not seem to change anything
        //usleep(10);
    }

    //printLog();
    cleanup();

    return 0;
}
