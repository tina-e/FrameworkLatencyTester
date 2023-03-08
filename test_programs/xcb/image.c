// based on https://www.x.org/releases/X11R7.7/doc/libxcb/tutorial/index.html
#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <png.h>

#define WIDTH 1920
#define HEIGHT 1080

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

int main ()
{
    xcb_connection_t    *c;
    xcb_screen_t        *screen;
    xcb_drawable_t       win;
    xcb_gcontext_t       foreground;
    xcb_gcontext_t       background;
    xcb_gcontext_t       img_context;
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

    unsigned char* pixels;
    read_png_file("noise.png", &pixels);

    xcb_pixmap_t pixmap = xcb_generate_id(c);
    img_context = xcb_generate_id(c);
    //xcb_image_t *image = xcb_image_create_native(c, WIDTH, HEIGHT, XCB_IMAGE_FORMAT_Z_PIXMAP, screen->root_depth, NULL, ~0, NULL);
    xcb_create_pixmap(c, screen->root_depth, pixmap, win, WIDTH, HEIGHT);
    xcb_create_gc(c, img_context, pixmap, 0, NULL);
    xcb_image_t *image = xcb_image_create_native(c, WIDTH, HEIGHT, XCB_IMAGE_FORMAT_Z_PIXMAP, screen->root_depth, pixels, WIDTH * HEIGHT * 4, pixels);
    xcb_image_put(c, pixmap, img_context, image, 0, 0, 0);
    xcb_image_destroy(image);

    /* Map the window on the screen */
    xcb_map_window (c, win);

    //xcb_set_input_focus(c, XCB_INPUT_FOCUS_POINTER_ROOT, win, XCB_CURRENT_TIME);


    /* We flush the request */
    xcb_flush (c);

    int running = 1;
    int pressed = 0;

    while (running && (e = xcb_wait_for_event (c))) {
        switch (e->response_type & ~0x80) {
            case XCB_EXPOSE:

                /* We draw the rectangles */
                xcb_poly_fill_rectangle (c, win, background, 1, rectangles);
                /*
                if (pressed)
                {
                    xcb_copy_area(c,
                            pixmap,
                            win,
                            img_context,
                            0, 0,
                            0, 0,
                            WIDTH,
                            HEIGHT);
                }
                else
                {
                    xcb_poly_fill_rectangle (c, win, background, 1, rectangles);
                }
                */

                /* We flush the request */
                xcb_flush (c);

                break;
            case XCB_BUTTON_PRESS:
                /* Handle the ButtonPress event type */
                //xcb_button_press_event_t *ev = (xcb_button_press_event_t *)e;

                pressed = 1;
                    xcb_copy_area(c,
                            pixmap,
                            win,
                            img_context,
                            0, 0,
                            0, 0,
                            WIDTH,
                            HEIGHT);

                /* We flush the request */
                xcb_flush (c);
                /* ... */

                break;
            case XCB_BUTTON_RELEASE:
                pressed = 0;
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
