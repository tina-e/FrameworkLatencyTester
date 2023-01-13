// thanks, ChatGPT
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv) {
    al_init();
    al_init_primitives_addon();
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
    al_set_window_title(display, "Allegro Test Application");
    al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    al_install_mouse();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);
    al_clear_to_color(color);
    al_flip_display();

    bool update = false;
    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            update = true;
            color = al_map_rgb(255, 255, 255);
        } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            update = true;
            color = al_map_rgb(0, 0, 0);
        }
        
        if (update) {
            al_clear_to_color(color);
            al_flip_display();
        }
    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    return 0;
}
