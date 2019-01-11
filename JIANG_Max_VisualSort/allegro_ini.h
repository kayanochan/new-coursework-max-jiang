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
#define RED      al_map_rgb(255, 0, 0)
#define GREEN    al_map_rgb(0, 255, 0)
#define BLUE    al_map_rgb(0, 0, 255)
#define YELLOW   al_map_rgb(255, 255, 0)
#define ORANGE   al_map_rgb(255, 127, 0)
#define LGREEN   al_map_rgb(93, 237, 179)
#define SKYBLUE  al_map_rgb(147, 204, 241)
#define PURPLE   al_map_rgb(48, 6, 85)
#define LPURPLE  al_map_rgb(75, 16, 149)
#define PINK     al_map_rgb(253, 199, 199)
#define BEIGE    al_map_rgb(232, 182, 133)
#define DARKSNOW al_map_rgb(17, 134, 247)
#define WOOD     al_map_rgb(219, 138, 80)
#define DARKWOOD al_map_rgb(189, 108, 50)
#define FLOOR    al_map_rgb(136, 63, 39)

// Initialize Frames per second
const float FPS = 256;
// Screen width
const float SW = 1100;
// Screen height
const float SH = 600;

int initializeAllegro(ALLEGRO_DISPLAY *&display, ALLEGRO_EVENT_QUEUE *&event_queue,
                      ALLEGRO_TIMER *&timer, ALLEGRO_FONT *&font);

#endif // _ALLEGRO_INI_H
