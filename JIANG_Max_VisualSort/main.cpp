#include "quicksort.h"
#include "mergesort.h"
#include "selectionsort.h"
#include <iostream>

int main(int argc, char *argv[]) {

    // Print instructions
    cout << "Welcome to Visual Sort" << endl
         << "'S' to randomize list" << endl
         << "'Q' to use quick sort" << endl
         << "'L' to use selection sort" << endl
         << "'M' to use merge sort" << endl
         << "'3' to change list size" << endl;

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

    // Initialize list
    vector<int> master;
    for (int i = 0; i < 200; i++) {
        master.push_back(i + 1);
    }
    scramble(master, font);

    // Draw screen
    drawGraph(master, font);

	while (!doexit) {

        // Wait for event
        al_wait_for_event(event_queue, &ev);
        al_get_mouse_state(&mouse);

        // Close the game
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            doexit = true;
        }
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
            doexit = true;
      	}

        // Randomize / Scramble on 'S'
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_S) {

                 scramble(master, font);
                 compares = 0;
                 swaps = 0;

      	}

        // Quick sort on 'Q'
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_Q) {

                compares = 0;
                swaps = 0;
                quicksort(master, master.size(), 0, font, compares, swaps);

      	}

        // Selection sort on 'L'
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_L) {

                compares = 0;
                swaps = 0;
                selectionsort(master, font, compares, swaps);

      	}

        // Merge sort on 'M'
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_M) {

                compares = 0;
                swaps = 0;
                mergesort(master, 0, master.size(), font, compares, swaps);

      	}

        // Change list size on '3'
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
                 ev.keyboard.keycode == ALLEGRO_KEY_3) {

                changeSize(master, font, event_queue, ev);

      	}

	}

    // Close the program
	al_destroy_display(display);

    return 0;

}
