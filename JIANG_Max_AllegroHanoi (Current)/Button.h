#ifndef _BUTTON_H
#define _BUTTON_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>
using namespace std;

class Button {

    private:

        // Dimensions
        float x1;
        float y1;
        float x2;
        float y2;

        // Text on button
        string text;

        // Aesthetics
        ALLEGRO_COLOR bColor;
        ALLEGRO_COLOR tColor;
        ALLEGRO_FONT *font;

        bool active;

    public:

        // Constructors and desctructor
        Button();
        Button(float a1, float b1, float a2, float b2,
               string t, const ALLEGRO_COLOR &c1,
               const ALLEGRO_COLOR &c2);
        ~Button();

        // Accessor
        bool isActive() const;

        // Modifiers
        void setText(string t);
        void setColor(ALLEGRO_COLOR c);
        void setTColor(ALLEGRO_COLOR c);
        void turnOn();
        void turnOff();

        // Other functions
        bool click(const ALLEGRO_MOUSE_STATE &mouse) const;
        void draw(const ALLEGRO_MOUSE_STATE &mouse) const;


};

#endif // _BUTTON_H
