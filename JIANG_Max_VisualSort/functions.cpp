#include "functions.h"

void drawGraph(const vector<int> &in, ALLEGRO_FONT *font, int compares, int swaps) {

    al_clear_to_color(BLACK);

    int big = in[0];
    for (int i = 1; i < in.size(); i++) {
        big = max(in[i], big);
    }

    for (int i = 0; i < in.size(); i++) {
        al_draw_filled_rectangle(100+(SW-200)/in.size()*i, SH-50-(SH-100)*(float)in[i]/big,
                                 100+(SW-200)/in.size()*(i+1), SH-50, GREY);
    }

    al_draw_textf(font, WHITE, SW / 3, SH - 50,
                  ALLEGRO_ALIGN_CENTER, "%d comparison(s)", compares);
    al_draw_textf(font, WHITE, 2 * SW / 3, SH - 50,
                  ALLEGRO_ALIGN_CENTER, "%d swap(s)", swaps);

    al_flip_display();

}

void scramble(vector<int> &in, ALLEGRO_FONT *font) {

    vector<int> deck;
    int temp, vecSize = in.size();
    for (int i = 0; i < in.size(); i++) {
        deck.push_back(in[i]);
    }
    in.clear();
    for (int i = 0; i < vecSize; i++) {
        temp = rand() % deck.size();
        in.push_back(deck[temp]);
        deck.erase(deck.begin()+temp);
    }
    drawGraph(in, font);
}

void changeSize(vector<int> &in, ALLEGRO_FONT *font,
                ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT &ev) {

    // Redraw screen
    al_clear_to_color(BLACK);
    al_draw_textf(font, WHITE, SW / 2, SH /2 ,
                         ALLEGRO_ALIGN_CENTER, "NEW SIZE: %d", in.size());
    al_flip_display();

    bool done = false;
    int typer = in.size();

    while (!done) {

        // Wait for event
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

            // Adding digits
            if (ev.keyboard.keycode >= 27 && ev.keyboard.keycode <= 36) {
                typer *= 10;
                typer += ev.keyboard.keycode - 27;

                // Redraw screen
                al_clear_to_color(BLACK);
                al_draw_textf(font, WHITE, SW / 2, SH /2 ,
                         ALLEGRO_ALIGN_CENTER, "NEW SIZE: %d", typer);
                al_flip_display();
            }

            // Deleting digits
            else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE ||
                     ev.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                typer /= 10;

                // Redraw screen
                al_clear_to_color(BLACK);
                al_draw_textf(font, WHITE, SW / 2, SH /2 ,
                         ALLEGRO_ALIGN_CENTER, "NEW SIZE: %d", typer);
                al_flip_display();
            }

            // Increment and decrement by 1

            else if (ev.keyboard.keycode == ALLEGRO_KEY_UP ||
                     ev.keyboard.keycode == ALLEGRO_KEY_W ||
                     ev.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
                     ev.keyboard.keycode == ALLEGRO_KEY_D ||
                     ev.keyboard.keycode == ALLEGRO_KEY_EQUALS ||
                     ev.keyboard.keycode == ALLEGRO_KEY_TAB ||
                     ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP) {
                if (!typer) typer = in.size();
                typer++;

                // Redraw screen
                al_clear_to_color(BLACK);
                al_draw_textf(font, WHITE, SW / 2, SH /2 ,
                         ALLEGRO_ALIGN_CENTER, "NEW SIZE: %d", typer);
                al_flip_display();
            }

            else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN ||
                     ev.keyboard.keycode == ALLEGRO_KEY_S ||
                     ev.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                     ev.keyboard.keycode == ALLEGRO_KEY_A ||
                     ev.keyboard.keycode == ALLEGRO_KEY_MINUS ||
                     ev.keyboard.keycode == ALLEGRO_KEY_COMMA) {
                if (!typer) typer = in.size();
                if (typer > 1) typer--;

                // Redraw screen
                al_clear_to_color(BLACK);
                al_draw_textf(font, WHITE, SW / 2, SH /2 ,
                         ALLEGRO_ALIGN_CENTER, "NEW SIZE: %d", typer);
                al_flip_display();
            }

            // Enter number
            else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                // Set new size
                in.clear();
                for (int i = 0; i < typer; i++) in.push_back(i + 1);
                al_clear_to_color(BLACK);
                drawGraph(in, font);
                done = true;
            }
        }

    }

}
