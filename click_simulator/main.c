#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <linux/uinput.h>

// create virtual input device with uinput
int init_uinput()
{
    struct uinput_setup usetup;
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    // add capability to emit a left mouse click
    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234;  // dummy vendor
    usetup.id.product = 0x5678; // dummy product
    strcpy(usetup.name, "autoclicker");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    return fd;
}

// use uinput to emit an input event
void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type; // e.g. key press
   ie.code = code; // e.g. left mouse button (272)
   ie.value = val; // e.g. "pressed" (1)

   // event timestamps are ignored
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}

void main(int argc, char** argv)
{
    int iterations = 100;   // number of clicks until the program ends
    int min_delay = 100000; // minimum delay between clicks in microseconds
    int max_delay = 500000; // maximum delay between clicks in microseconds
    int pre_delay = 1;      // delay before the program starts in seconds

    if(argc > 1) iterations = atoi(argv[1]);
    if(argc > 2) min_delay = atoi(argv[2]);
    if(argc > 3) max_delay = atoi(argv[3]);
    if(argc > 4) pre_delay = atoi(argv[4]);

    int fd_uinput = init_uinput();

    sleep(pre_delay);

    srand(0);

    for (int i = 0; i < iterations; i++) {
        // click
        emit(fd_uinput, EV_KEY, BTN_LEFT, 1);
        emit(fd_uinput, EV_SYN, SYN_REPORT, 0);

        // wait to make sure the click event was registerd
        usleep(200000);

        // release click
        emit(fd_uinput, EV_KEY, BTN_LEFT, 0);
        emit(fd_uinput, EV_SYN, SYN_REPORT, 0);

        // wait for random time between min_delay and max_delay microseconds
        // this way we make sure we don't accidentaly sync with anything
        usleep(min_delay + (rand() % (max_delay - min_delay)));
    }

    sleep(1);

    ioctl(fd_uinput, UI_DEV_DESTROY);
    close(fd_uinput);
}
