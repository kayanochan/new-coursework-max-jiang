#include "Button.h"
#include <string>
using namespace std;

// Constructors and desctructor
Button::Button() {

}

Button::Button(float a1, float b1, float a2, float b2,
               string t, const ALLEGRO_COLOR &c1,
               const ALLEGRO_COLOR &c2) {

    x1 = a1;
    y1 = b1;
    x2 = a2;
    y2 = b2;
    text = t;
    bColor = c1;
    tColor = c2;
    font = al_load_ttf_font("comic.ttf", 20, 0);
    active = true;

}

Button::~Button() {

}

// Check if active
bool Button::isActive() const {

    return active;

}

// Modifiers

void Button::setText(string t) {

    text = t;

}

void Button::setColor(ALLEGRO_COLOR c) {

    bColor = c;

}

void Button::setTColor(ALLEGRO_COLOR c) {

    tColor = c;

}

void Button::turnOn() {

    active = true;

}

void Button::turnOff() {

    active = false;

}

// Check for click
bool Button::click(const ALLEGRO_MOUSE_STATE &mouse) const {

    bool out = false;

    // If mouse is inside the button
    if (mouse.x <= x2 && mouse.x >= x1 &&
        mouse.y <= y2 && mouse.y >= y1)

        out = true;

    return out;

}

// Draw button
void Button::draw(const ALLEGRO_MOUSE_STATE &mouse) const {

    // Split cases if active or not
    if (active) {

        // Calculate shade modifier if mouse hovering or on click
        float adder = 0;
        if (click(mouse)) {

            adder -= 20;

            if ((mouse.buttons & 1) || (mouse.buttons & 2))
                adder -= 20;

        }

        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, (y2-y1)/3, (y2-y1)/3,
                                     al_map_rgb(max(255*bColor.r+adder, (float)0),
                                                max(255*bColor.g+adder, (float)0),
                                                max(255*bColor.b+adder, (float)0)));
    }

    else {

        // Draw grey button if inactive
        al_draw_filled_rounded_rectangle(x1, y1, x2, y2, (y2-y1)/3, (y2-y1)/3,
                                         al_map_rgb(127, 127, 127));

    }

    // Write text
    al_draw_text(font, tColor, (x1+x2)/2, (y1+y2)/2-10,
                 ALLEGRO_ALIGN_CENTER, text.c_str());

}
