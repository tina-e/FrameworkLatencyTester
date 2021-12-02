#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <linux/uinput.h>

void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   // event timestamps are ignored
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}

void main(int argc, char** argv)
{
    int iterations = 100;
    int min_delay = 100000;
    int max_delay = 900000;
    int pre_delay = 1;

    if(argc > 1) iterations = atoi(argv[1]);
    if(argc > 2) min_delay = atoi(argv[2]);
    if(argc > 3) max_delay = atoi(argv[3]);
    if(argc > 4) pre_delay = atoi(argv[4]);

    struct uinput_setup usetup;

    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, BTN_LEFT);

    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; // dummy vendor
    usetup.id.product = 0x5678; // dummy product
    strcpy(usetup.name, "autoclicker");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    sleep(pre_delay);

    srand(0);

    for (int i = 0; i < iterations; i++) {
        emit(fd, EV_KEY, BTN_LEFT, 1);
        emit(fd, EV_SYN, SYN_REPORT, 0);
        usleep(min_delay + (rand() % (max_delay - min_delay)));
        emit(fd, EV_KEY, BTN_LEFT, 0);
        emit(fd, EV_SYN, SYN_REPORT, 0);
        usleep(200000);
    }

    sleep(1);

    ioctl(fd, UI_DEV_DESTROY);
    close(fd);
}
