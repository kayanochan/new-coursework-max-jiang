#ifndef _ALLEGRO_INI_H
#define _ALLEGRO_INI_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

// Define Allegro colors
#define BLACK	 al_map_rgb(0, 0, 0)
#define WHITE	 al_map_rgb(255, 255, 255)
#define GREY	 al_map_rgb(127, 127, 127)

// Initialize Frames per second
const float FPS = 256;
// Screen width
const float SW = 1100;
// Screen height
const float SH = 600;

int initializeAllegro(ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue,
                      ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&font);

#endif // _ALLEGRO_INI_H
