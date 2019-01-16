#include "quicksort.h"
#include "mergesort.h"
#include "selectionsort.h"
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
    // Font
    ALLEGRO_FONT *font;

    // Initialize Allegro
    initializeAllegro(display, event_queue, timer, font);

    // Declare and initialize variables
    bool doexit = false;
    ALLEGRO_EVENT ev;
    ALLEGRO_MOUSE_STATE mouse;
    int compares = 0, swaps = 0;
    vector<int> master;
    for (int i = 0; i < 100; i++) {
        master.push_back(i);
    }
    scramble(master, font);

    drawGraph(master, font);

	while (!doexit) {

        // Wait for event
        al_wait_for_event(event_queue, &ev);
        al_get_mouse_state(&mouse);

        // Close the game
      	if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            doexit = true;
      	}

      	if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_S) {
                 scramble(master, font);
                 compares = 0;
                 swaps = 0;
      	}
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_Q) {
                 quicksort(master, master.size(), 0, font, compares, swaps);
      	}
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_L) {
                 selectionsort(master, font, compares, swaps);
      	}
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_M) {
                 mergesort(master, 0, master.size(), font, compares, swaps);
      	}

	}

	al_destroy_display(display);

    return 0;

}
