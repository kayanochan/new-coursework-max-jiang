#include "quicksort.h"
#include "mergesort.h"
#include <iostream>

int main(int argc, char *argv[]) {

    // Seed random
	srand(time(0));

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
    vector<int> master;
    for (int i = 0; i < 1000; i++) {
        master.push_back(rand()%1000+1);
    }
    scramble(master);

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

            al_draw_filled_circle(SW / 2, SH / 2, 150, YELLOW);

            drawGraph(master);

      	}

      	if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_S) {
                 scramble(master);
      	}
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                 quicksort(master, master.size(), 0);
      	}

      	al_flip_display();

	}

	al_destroy_display(display);

    return 0;

}
