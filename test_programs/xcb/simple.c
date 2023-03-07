// based on https://www.x.org/releases/X11R7.7/doc/libxcb/tutorial/index.html
#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>

int main ()
{
    xcb_connection_t    *c;
    xcb_screen_t        *screen;
    xcb_drawable_t       win;
    xcb_gcontext_t       foreground;
    xcb_gcontext_t       background;
    xcb_generic_event_t *e;
    uint32_t             mask = 0;
    uint32_t             values[2];

    xcb_rectangle_t      rectangles[] = {
        { 0, 0, 1920, 1080}};

    /* Open the connection to the X server */
    c = xcb_connect (NULL, NULL);

    /* Get the first screen */
    screen = xcb_setup_roots_iterator (xcb_get_setup (c)).data;

    /* Create black (foreground) graphic context */
    win = screen->root;

    foreground = xcb_generate_id (c);
    mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    values[0] = screen->white_pixel;
    values[1] = 0;
    xcb_create_gc (c, foreground, win, mask, values);

    background = xcb_generate_id (c);
    mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
    values[0] = screen->black_pixel;
    values[1] = 0;
    xcb_create_gc (c, background, win, mask, values);

    /* Ask for our window's Id */
    win = xcb_generate_id(c);

    /* Create the window */
    mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    values[0] = screen->black_pixel;
    values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS | XCB_EVENT_MASK_BUTTON_RELEASE;
    xcb_create_window (c,                             /* Connection          */
            XCB_COPY_FROM_PARENT,          /* depth               */
            win,                           /* window Id           */
            screen->root,                  /* parent window       */
            0, 0,                          /* x, y                */
            1920, 1080,                      /* width, height       */
            0,                            /* border_width        */
            XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
            screen->root_visual,           /* visual              */
            mask, values);                 /* masks */

    values[0] = 1;
    values[1] = 0;
    xcb_change_window_attributes (c, win, XCB_CW_OVERRIDE_REDIRECT, values);
    /* Map the window on the screen */
    xcb_map_window (c, win);

    //xcb_set_input_focus(c, XCB_INPUT_FOCUS_POINTER_ROOT, win, XCB_CURRENT_TIME);

    /* We flush the request */
    xcb_flush (c);

    while ((e = xcb_wait_for_event (c))) {
        switch (e->response_type & ~0x80) {
            case XCB_EXPOSE:

                /* We draw the rectangles */
                xcb_poly_fill_rectangle (c, win, background, 1, rectangles);

                /* We flush the request */
                xcb_flush (c);

                break;
            case XCB_BUTTON_PRESS:
                /* Handle the ButtonPress event type */
                xcb_button_press_event_t *ev = (xcb_button_press_event_t *)e;

                /* We draw the rectangles */
                xcb_poly_fill_rectangle (c, win, foreground, 1, rectangles);

                /* We flush the request */
                xcb_flush (c);
                /* ... */

                break;
            case XCB_BUTTON_RELEASE:
                /* Handle the ButtonPress event type */
                //xcb_button_press_event_t *ev = (xcb_button_press_event_t *)e;

                /* We draw the rectangles */
                xcb_poly_fill_rectangle (c, win, background, 1, rectangles);

                /* We flush the request */
                xcb_flush (c);

                /* ... */

                break;

            default:
                /* Unknown event type, ignore it */
                break;
        }
        /* Free the Generic Event */
        free (e);
    }

    return 0;
}
