#include "quicksort.h"
#include "mergesort.h"
#include <iostream>

int main(int argc, char *argv[]) {

    // Display
    ALLEGRO_DISPLAY *display = nullptr;
    // Event queue object
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    // Timer object
    ALLEGRO_TIMER *timer = nullptr;
    // Writing font
    ALLEGRO_FONT *font;

    // Initialize Allegro
    initializeAllegro(display, event_queue, timer, font);

    // Declare and initialize variables
    bool doexit = false;
    ALLEGRO_EVENT ev;
    ALLEGRO_MOUSE_STATE mouse;

	// Seed random
	srand(time(0));

	while (!doexit) {

        // Wait for event
        al_wait_for_event(event_queue, &ev);
        al_get_mouse_state(&mouse);

        // Close the game
      	if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            doexit = true;
      	}

      	// On timer
      	else if (ev.type == ALLEGRO_EVENT_TIMER) {

            al_clear_to_color(BLACK);

            al_draw_circle(SW / 2, SH / 2, 150, WHITE, 10);

      	}

      	al_flip_display();

	}

	al_destroy_display(display);

    return 0;

}
