#include "allegro_ini.h"

int initializeAllegro(ALLEGRO_DISPLAY *display, ALLEGRO_EVENT_QUEUE *event_queue,
                      ALLEGRO_TIMER *timer, ALLEGRO_FONT *font) {

    // Initialize Allegro
    al_init();

    // Initialize display
    display = al_create_display(SW, SH);
    if (!display) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize display!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    al_set_window_title(display, "Sorting");
	// Initialize keyboard routines
	if (!al_install_keyboard()) {
	    al_show_native_message_box(display, "Error", "Error",
                                   "Failed to initialize the keyboard!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
   	}
    // Initialize mouse routines
    if (!al_install_mouse()) {
	    al_show_native_message_box(display, "Error", "Error",
                                   "Failed to initialize the mouse!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
     	return -1;
    }
    // Initialize the image processor
 	if (!al_init_image_addon()) {
    	al_show_native_message_box(display, "Error", "Error",
                                   "Failed to initialize the image add-on!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
	// Set up the timer
	timer = al_create_timer(1.0 / FPS);
   	if (!timer) {
   		al_show_native_message_box(display, "Error", "Error",
                                   "Failed to create the timer!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
	// Set up the event queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error",
                                   "Failed to create the event queue!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
      	return -1;
	}
	if (!al_init_primitives_addon()) {
    	al_show_native_message_box(display, "Error", "Error",
                                   "Failed to initialize primatives add-on!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
    	return -1;
	}
	// Initialize the font add on
	al_init_font_addon();
	// Initialize the ttf (True Type Font) add on
    al_init_ttf_addon();
    font = al_load_ttf_font("comic.ttf", 20, 0);
    if (!font) {
        al_show_native_message_box(display, "Error", "Error",
                                   "Could not load comic.ttf!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Register timer events
    al_register_event_source(event_queue,
                             al_get_display_event_source(display));
 	al_register_event_source(event_queue,
                             al_get_keyboard_event_source());
 	al_register_event_source(event_queue,
                             al_get_mouse_event_source());
	al_register_event_source(event_queue,
                             al_get_timer_event_source(timer));
	// Start the timer
	al_start_timer(timer);

}
