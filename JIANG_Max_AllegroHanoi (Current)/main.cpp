/**********************************************
* Tower of Hanoi - Interaction general solver *
* Uses Allegro interface                      *
* Allows for a high level of user interaction *
* Usable with mouse or keyboard               *
* General solving algorithm from any position *
* Many aesthetic options                      *
* A bit slow at startup                       *
* Max Jiang                                   *
* ICS4U                                       *
* 11/22/2018                                  *
**********************************************/

#include "Peg.h"
#include "Button.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
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

// Screen dimensions (for reference only)
const int SW = 1600;
const int SH = 900;

// Prototype functions
void draw(int n, int pos, int height, int peg, int theme,
          const ALLEGRO_DISPLAY_MODE &disp_data);
void execute(int nMove, Peg pegs[3]);
int reverseMove(int m);
vector<int> solve(int height, int peg1, int peg2);
int findRing(int pos, Peg pegs[3]);
vector<int> solveArb(int height, Peg pegs[3]);
vector<int> solveArb2(int height, Peg pegs[3], int dest);
vector<int> simplify(vector<int> sol);
vector<float> rainbow(int pos, int height, int theme);
void doAnimate(Button &animate, Button &movedown, Button &moveup,
               Button &pegNum, Button &shuffler,
               bool &play, bool done, bool &during,
               int &moveCount, int height, int &solLen,
               Peg pegs[3], vector<int> &solution,
               const ALLEGRO_DISPLAY_MODE &disp_data,
               ALLEGRO_FONT *font);
void doMoveup(const Button &moveup, Button &movedown,
              Peg pegs[3], bool &done, bool &during,
              int &moveCount, int &solLen, int height,
              vector<int> &solution,
              const ALLEGRO_DISPLAY_MODE &disp_data,
              ALLEGRO_FONT *font);
void doMovedown(const Button &movedown, Peg pegs[3],
                int &moveCount, const vector<int> &solution);
void doReset(const Button &reset, Peg pegs[3],
             bool &play, bool &during, bool &done,
             int height);
void shuffle(int height, Peg pegs[3]);
void doShuffler(const Button &shuffler, Button &movedown, Peg pegs[3],
                int height, bool &during, bool &done);
void doNight(Button &night, ALLEGRO_COLOR &textColor,
             bool &nightmode);

// Main program
int main(int argc, char *argv[]) {

    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_DISPLAY_MODE   disp_data;
    // Add event queue object
	ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
	// Add timer object
	ALLEGRO_TIMER *timer = nullptr;
	// Initialize Allegro
	al_init();
	// Initialize display
    al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    display = al_create_display(disp_data.width, disp_data.height);
	if (!display) {
    	al_show_native_message_box(display, "Error", "Error",
                                "Failed to initialize display!",
                                 nullptr, ALLEGRO_MESSAGEBOX_ERROR);
       	return -1;
	}
	al_set_window_title(display, "Tower of Hanoi");
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
    ALLEGRO_FONT *font = al_load_ttf_font("comic.ttf", 20, 0);
    if (!font) {
        al_show_native_message_box(display, "Error", "Error",
                                   "Could not load comic.ttf!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }
    ALLEGRO_FONT *font2 = al_load_ttf_font("comic.ttf", 50, 0);
    if (!font2) {
        al_show_native_message_box(display, "Error", "Error",
                                   "Could not load comic.ttf!",
                                   nullptr, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // Declare and initialize variables
    bool doexit = false;
    ALLEGRO_EVENT ev;
    ALLEGRO_MOUSE_STATE mouse;

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

	// Seed random
	srand(time(0));

    // Draw title/loading screen
	al_clear_to_color(WHITE);
	al_draw_text(font2, RED, disp_data.width/2, disp_data.height/4,
              ALLEGRO_ALIGN_CENTER, "TOWER");
    al_draw_text(font2, YELLOW, disp_data.width/2, disp_data.height/2,
              ALLEGRO_ALIGN_CENTER, "OF");
    al_draw_text(font2, BLUE, disp_data.width/2, 3*disp_data.height/4,
              ALLEGRO_ALIGN_CENTER, "HANOI");
    al_flip_display();

    // Declare and initialize variables
    int height = 7, move1 = 0, move2 = 0,
        holder, metro = 0, moveCount = 0,
        solLen, speed = 16, typer = 0,
        theme = 0, temptheme, snowflake[50][2];
    Peg pegs[3];
    for (int i = height; i > 0; i--) {
        pegs[0].push(i);
    }
    vector<int> solution = solve(7, 0, 2), sol20 = solve(20, 0, 2);
    bool hold = false, mousedown = false,
         valid = true, play = false,
         done = true, during = false,
         enter = false, themeChoose = false,
         nightmode = false;
    ALLEGRO_COLOR textColor = BLACK;

    // Buttons

    // Main screen buttons
    Button animate(17*disp_data.width/40, 11*disp_data.height/42,
                   23*disp_data.width/40, 17*disp_data.height/42,
                   "SOLVE", GREEN, BLACK);
    Button moveup(71*disp_data.width/120, 11*disp_data.height/42,
                  89*disp_data.width/120, 17*disp_data.height/42,
                  "->", GREEN, BLACK);
    Button movedown(31*disp_data.width/120, 11*disp_data.height/42,
                49*disp_data.width/120, 17*disp_data.height/42,
                "<-", GREEN, BLACK);
    movedown.turnOff();
    Button fast(91*disp_data.width/120, 11*disp_data.height/42,
                109*disp_data.width/120, 17*disp_data.height/42,
                ">>", GREEN, BLACK);
    Button slow(11*disp_data.width/120, 11*disp_data.height/42,
                29*disp_data.width/120, 17*disp_data.height/42,
                "<<", GREEN, BLACK);
    Button menu(17*disp_data.width/40, 2*disp_data.height/21,
                   23*disp_data.width/40, 5*disp_data.height/21,
                   "THEME", YELLOW, BLACK);
    Button reset(91*disp_data.width/120, 2*disp_data.height/21,
                  109*disp_data.width/120, 5*disp_data.height/21,
                  "RESET", RED, BLACK);
    reset.turnOff();
    Button pegNum(11*disp_data.width/120, 2*disp_data.height/21,
                  29*disp_data.width/120, 5*disp_data.height/21,
                  "SET PEG #", BEIGE, BLACK);
    Button shuffler(31*disp_data.width/120, 2*disp_data.height/21,
                  49*disp_data.width/120, 5*disp_data.height/21,
                  "SHUFFLE", YELLOW, BLACK);
    Button night(71*disp_data.width/120, 2*disp_data.height/21,
                    89*disp_data.width/120, 5*disp_data.height/21,
                    "NIGHT MODE", BLACK, WHITE);
    Button esc(193*disp_data.width/200, disp_data.height/180,
               99*disp_data.width/100, disp_data.height/20,
               "X", RED, WHITE);

    // Theme choser buttons
    Button tRainbow(17*disp_data.width/40, 2*disp_data.height/21,
                    23*disp_data.width/40, 5*disp_data.height/21,
                    "RAINBOW", DARKSNOW, BLACK);
    Button tHalloween(17*disp_data.width/40, 11*disp_data.height/42,
                   23*disp_data.width/40, 17*disp_data.height/42,
                   "HALLOWEEN", ORANGE, BLACK);
    Button tChristmas(17*disp_data.width/40, 3*disp_data.height/7,
                   23*disp_data.width/40, 4*disp_data.height/7,
                   "X-MAS", RED, GREEN);
    Button tEaster(17*disp_data.width/40, 25*disp_data.height/42,
                   23*disp_data.width/40, 31*disp_data.height/42,
                   "EASTER", PINK, LGREEN);
    Button tPlain(17*disp_data.width/40, 16*disp_data.height/21,
                  23*disp_data.width/40, 19*disp_data.height/21,
                   "PLAIN", DARKWOOD, BLACK);

	// Main game
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

            // Background color (based on theme)
            if (theme == 1) {
                if (nightmode) al_clear_to_color(PURPLE);
                else al_clear_to_color(LPURPLE);
            }
            else if (theme == 2) {
                if (nightmode) al_clear_to_color(BLACK);
                else al_clear_to_color(SKYBLUE);
            }
            else {
                if (nightmode) al_clear_to_color(BLACK);
                else al_clear_to_color(WHITE);
            }

            // Peg number choosing screen
            if (enter) {

                // Write instructions
                al_draw_text(font2, textColor, disp_data.width/2,
                             disp_data.height/3, ALLEGRO_ALIGN_CENTER,
                             "ENTER NEW PEG NUMBER:");
                // Default to writing current height
                if (typer)
                    al_draw_textf(font2, textColor, disp_data.width/2,
                                  2*disp_data.height/3, ALLEGRO_ALIGN_CENTER,
                                  "%d", typer);
                // Write new user-entered number
                else
                    al_draw_textf(font2, textColor, disp_data.width/2,
                                  2*disp_data.height/3, ALLEGRO_ALIGN_CENTER,
                                  "%d", height);

            }

            // Theme choosing screen
            else if (themeChoose) {

                // Draw buttons
                tRainbow.draw(mouse);
                tHalloween.draw(mouse);
                tChristmas.draw(mouse);
                tEaster.draw(mouse);
                tPlain.draw(mouse);
                // Draw selection arrow
                al_draw_text(font2, textColor, 5*disp_data.width/8,
                             (theme+(float)11/14)*disp_data.height/6,
                             ALLEGRO_ALIGN_LEFT, "<");

            }

            // Main screen
            else {

                // Christmas theme background
                if (theme == 2) {
                    // Night
                    if (nightmode) {
                        // Draw snow, moon, stars
                        al_draw_filled_rectangle(0, 3*disp_data.height/4,
                                                 disp_data.width,
                                                 disp_data.height, DARKSNOW);
                        al_draw_filled_circle(91*disp_data.width/120,
                                              2*disp_data.height/21,
                                              disp_data.width/10, YELLOW);
                        for (int i = 0; i < 50; i++)
                            al_draw_filled_circle(snowflake[i][0],
                                                  snowflake[i][1],
                                                  (float)disp_data.width/400,
                                                  YELLOW);
                    }
                    // Day
                    else {
                        // Draw snow, snowflakes
                        al_draw_filled_rectangle(0, 3*disp_data.height/4,
                                                 disp_data.width,
                                                 disp_data.height, WHITE);
                        for (int i = 0; i < 50; i++)
                            al_draw_filled_circle(snowflake[i][0],
                                                  snowflake[i][1],
                                                  (float)disp_data.width/200,
                                                  WHITE);
                    }
                }

                // Draw buttons
                animate.draw(mouse);
                moveup.draw(mouse);
                movedown.draw(mouse);
                fast.draw(mouse);
                slow.draw(mouse);
                menu.draw(mouse);
                reset.draw(mouse);
                pegNum.draw(mouse);
                shuffler.draw(mouse);
                night.draw(mouse);
                esc.draw(mouse);

                // Draw pegs, floor
                al_draw_filled_rectangle(0, disp_data.height-10,
                                         disp_data.width, disp_data.height,
                                         FLOOR);
                for (int i = 1; i < 4; i++)
                    al_draw_filled_rectangle(i*disp_data.width/4-10,
                                             disp_data.height-10,
                                             i*disp_data.width/4+10,
                                             disp_data.height/2, WOOD);

                // Write speed
                al_draw_textf(font, textColor, disp_data.width/2,
                              17*disp_data.height/42,
                              ALLEGRO_ALIGN_CENTER, "%.3gx speed", 16.0/speed);

                // Do move if appropriate
                if (play) {
                    if (!(metro%speed)) {
                        execute(solution[moveCount], pegs);
                        done = false;
                        moveCount++;
                    }
                    metro++;
                }

                // Turn off movedown if at beginning of solution
                if (!moveCount) {
                    movedown.turnOff();
                }

                // Check for solved state
                if ((pegs[0].length() == height ||
                    pegs[1].length() == height ||
                    pegs[2].length() == height) && !done) {

                    // Modify appropriate variables
                    done = true;
                    play = false;
                    moveCount = 0;
                    solution.clear();

                    // Generate new solution
                    if (pegs[2].length())
                        solution = solve(height, 2, 0);
                    else if (pegs[1].length())
                        solution = solve(height, 1, 2);
                    else {
                        if (pegs[0].length() >= 20)
                            solution = sol20;
                        else
                            solution = solve(height, 0, 2);
                    }

                    // Modify appropriate variables
                    solLen = solution.size();
                    animate.setText("SOLVE");
                    animate.setColor(GREEN);
                    animate.turnOn();
                    moveup.turnOn();
                    pegNum.turnOn();
                    shuffler.turnOn();

                }

                // Check if reset is available
                if (!hold) {
                    if (!reset.isActive() && pegs[0].length() != height)
                        reset.turnOn();
                    else if (reset.isActive() && pegs[0].length() == height)
                        reset.turnOff();
                }

                // Draw rings
                for (int i = 0; i < 3; i++) {
                    if (pegs[i].length()) {
                        vector<int> temp;
                        temp = pegs[i].getDisk();
                        for (int j = 0; j < pegs[i].length(); j++)
                            draw(temp[j], j, height, i+1, theme, disp_data);
                    }
                }

                // Draw dragged ring
                if (hold) {
                    vector<float> temp = rainbow(holder, height, theme);
                    al_draw_filled_rectangle(mouse.x-(float)holder/height*
                                             (disp_data.width/8-10)-10,
                                             mouse.y-(float)1/(height+1)*
                                             (disp_data.height/2-10)/2+5,
                                             mouse.x+(float)holder/height*
                                             (disp_data.width/8-10)+10,
                                             mouse.y+(float)1/(height+1)*
                                             (disp_data.height/2-10)/2+5,
                                             al_map_rgb(temp[0],temp[1],
                                                        temp[2]));
                }

            }

      	}

        // On click
      	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN &&
            !enter) {

            // Theme choosing screen
            if (themeChoose) {

                // Rainbow theme
                if (tRainbow.click(mouse)) {
                    theme = 0;
                    themeChoose = false;
                }

                // Halloween theme
                else if (tHalloween.click(mouse)) {
                    theme = 1;
                    themeChoose = false;
                }

                // Christmas theme
                else if (tChristmas.click(mouse)) {
                    theme = 2;
                    // Generate snowflakes
                    for (int i = 0; i < 50; i++) {
                        snowflake[i][0] = rand() % (int)disp_data.width;
                        snowflake[i][1] = rand() % (3*(int)disp_data.height)/4;
                    }
                    themeChoose = false;
                }

                // Easter theme
                else if (tEaster.click(mouse)) {
                    theme = 3;
                    themeChoose = false;
                }

                // Plain theme
                else if (tPlain.click(mouse)) {
                    theme = 4;
                    themeChoose = false;
                }

            }

            // Main screen
            else {

                // Track mouse button hold
                mousedown = true;

                // Exit button
                if (esc.click(mouse)) doexit = true;

                // Play/animate button
                else if (animate.click(mouse))
                    doAnimate(animate, movedown, moveup,
                              pegNum, shuffler,
                              play, done, during,
                              moveCount, height, solLen,
                              pegs, solution,
                              disp_data, font);

                // Move forward button
                else if (moveup.click(mouse))
                    doMoveup(moveup, movedown,
                             pegs, done, during,
                             moveCount, solLen, height,
                             solution,
                             disp_data, font);

                // Move backward button
                else if (movedown.click(mouse))
                    doMovedown(movedown, pegs,
                               moveCount, solution);

                // Fast forward button
                else if (fast.click(mouse)) {
                    if (speed > 1) {
                        speed /= 2;
                        // Turn on/off buttons appropriately
                        if (speed == 1) fast.turnOff();
                        else if (speed == 128) slow.turnOn();
                    }
                }

                // Slow down button
                else if (slow.click(mouse)) {
                    if (speed < 256) {
                        speed *= 2;
                        // Turn on/off buttons appropriately
                        if (speed == 2) fast.turnOn();
                        else if (speed == 256) slow.turnOff();
                    }
                }

                // Reset button
                else if (reset.click(mouse))
                    doReset(reset, pegs,
                            play, during, done,
                            height);

                // Peg num button
                else if (pegNum.click(mouse)) {
                    if (pegNum.isActive()) enter = true;
                }

                // Theme chooser button
                else if (menu.click(mouse))
                    themeChoose = true;

                // Shuffle button
                else if (shuffler.click(mouse)) {
                    if (shuffler.isActive())
                        doShuffler(shuffler, movedown, pegs,
                                   height, during, done);
                }

                // Night Mode button
                else if (night.click(mouse)) {
                    doNight(night, textColor,
                            nightmode);
                }

                // Dragging rings
                else {
                    if (!play) {
                        for (int i = 0; i < 3; i++) {
                            if (mouse.x > (2*i+1)*disp_data.width/8 &&
                                mouse.x < (2*i+3)*disp_data.width/8) {
                                if (!move1) {
                                    // Keep track of held ring
                                    holder = pegs[i].pop();
                                    if (holder != -1) {
                                        move1 = i+1;
                                        hold = true;
                                    }
                                }
                            }
                        }
                    }
                }

            }

      	}

        // Mouse button release
      	else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                !enter && !themeChoose && mousedown) {

            // Release if holding
            if (hold) {

                // Drop
                for (int i = 0; i < 3; i++) {
                    // Check which peg to drop
                    if (mouse.x > (2*i+1)*disp_data.width/8 &&
                        mouse.x < (2*i+3)*disp_data.width/8
                        && (!pegs[i].length() || holder < pegs[i].getTop())) {
                        move2 = i+1;
                        pegs[i].push(holder);
                        if ((done || during) &&
                            (move1 != move2)) {
                            // If there is change during a solve
                            done = false;
                            during = false;
                            animate.setText("SOLVE");
                        }
                        valid = true;
                    }
                }

                // If the drop is invalid
                if (!valid)
                    // Drop to whence it came
                    pegs[move1-1].push(holder);

                // Reset variables
                move1 = 0;
                valid = false;
                hold = false;

            }

            mousedown = false;

        }

        // On key press
      	else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {

            // Peg number screen
            if (enter) {

                // Digit entering
                if (ev.keyboard.keycode >= 27 && ev.keyboard.keycode <= 36) {
                    typer *= 10;
                    typer += ev.keyboard.keycode - 27;
                }

                // Deleting digits
                else if (ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE ||
                         ev.keyboard.keycode == ALLEGRO_KEY_DELETE) {
                    typer /= 10;
                }

                // Increment and decrement by 1

                else if (ev.keyboard.keycode == ALLEGRO_KEY_UP ||
                         ev.keyboard.keycode == ALLEGRO_KEY_W ||
                         ev.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
                         ev.keyboard.keycode == ALLEGRO_KEY_D ||
                         ev.keyboard.keycode == ALLEGRO_KEY_EQUALS ||
                         ev.keyboard.keycode == ALLEGRO_KEY_TAB ||
                         ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP) {
                    if (!typer) typer = height;
                    typer++;
                }

                else if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN ||
                         ev.keyboard.keycode == ALLEGRO_KEY_S ||
                         ev.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                         ev.keyboard.keycode == ALLEGRO_KEY_A ||
                         ev.keyboard.keycode == ALLEGRO_KEY_MINUS ||
                        ev.keyboard.keycode == ALLEGRO_KEY_COMMA) {
                    if (!typer) typer = height;
                    if (typer > 1) typer--;
                }

                // Enter number
                else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    // Set new height, reset pegs
                    if (typer) {
                        height = typer;
                        typer = 0;
                    }
                    for (int i = 0; i < 3; i++) pegs[i].toEmpty();
                    for (int i = height; i > 0; i--) pegs[0].push(i);
                    // New tower is solved, but trigger solution generation
                    done = false;
                    enter = false;
                }

            }

            // Theme choosing screen
            else if (themeChoose) {

                // Use arrow keys to scroll through menu

                if (ev.keyboard.keycode == ALLEGRO_KEY_DOWN ||
                    ev.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
                    ev.keyboard.keycode == ALLEGRO_KEY_S ||
                    ev.keyboard.keycode == ALLEGRO_KEY_D ||
                    ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP ||
                    ev.keyboard.keycode == ALLEGRO_KEY_SPACE ||
                    ev.keyboard.keycode == ALLEGRO_KEY_TAB ||
                    ev.keyboard.keycode == ALLEGRO_KEY_EQUALS) {
                    if (theme == 4) theme = 0;
                    else theme++;
                }

                else if (ev.keyboard.keycode == ALLEGRO_KEY_UP ||
                    ev.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                    ev.keyboard.keycode == ALLEGRO_KEY_W ||
                    ev.keyboard.keycode == ALLEGRO_KEY_A ||
                    ev.keyboard.keycode == ALLEGRO_KEY_COMMA ||
                    ev.keyboard.keycode == ALLEGRO_KEY_MINUS) {
                    if (!theme) theme = 4;
                    else theme--;
                }

                // Select theme by number
                else if (ev.keyboard.keycode >= 28 &&
                         ev.keyboard.keycode <= 32)
                    theme = ev.keyboard.keycode - 28;

                // Enter choice
                else if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (theme == 2) {
                        for (int i = 0; i < 50; i++) {
                            snowflake[i][0] = rand() % (int)disp_data.width;
                            snowflake[i][1] = rand() % (3*(int)disp_data.height)/4;
                        }
                    }
                    themeChoose = false;
                }

            }

            // Main screen
            else {

                // Play/animate
                if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE ||
                    ev.keyboard.keycode == ALLEGRO_KEY_ENTER ||
                    ev.keyboard.keycode == ALLEGRO_KEY_P)
                    doAnimate(animate, movedown, moveup,
                              pegNum, shuffler,
                              play, done, during,
                              moveCount, height, solLen,
                              pegs, solution,
                              disp_data, font);

                // Move forward
                else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT ||
                         ev.keyboard.keycode == ALLEGRO_KEY_D ||
                         ev.keyboard.keycode == ALLEGRO_KEY_EQUALS ||
                         ev.keyboard.keycode == ALLEGRO_KEY_TAB)
                    doMoveup(moveup, movedown,
                             pegs, done, during,
                             moveCount, solLen, height, solution,
                             disp_data, font);

                // Move back
                else if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT ||
                         ev.keyboard.keycode == ALLEGRO_KEY_A ||
                         ev.keyboard.keycode == ALLEGRO_KEY_MINUS)
                    doMovedown(movedown, pegs,
                               moveCount, solution);

                // Speed up
                else if ((ev.keyboard.keycode == ALLEGRO_KEY_FULLSTOP ||
                         ev.keyboard.keycode == ALLEGRO_KEY_UP ||
                         ev.keyboard.keycode == ALLEGRO_KEY_W) &&
                         fast.isActive()) {
                    if (speed > 1) {
                        speed /= 2;
                        // Turn on/off buttons appropriately
                        if (speed == 1) fast.turnOff();
                        else if (speed == 128) slow.turnOn();
                    }
                }

                // Slow down
                else if ((ev.keyboard.keycode == ALLEGRO_KEY_COMMA ||
                         ev.keyboard.keycode == ALLEGRO_KEY_DOWN) &&
                         slow.isActive()) {
                    if (speed < 256) {
                        speed *= 2;
                        // Turn on/off buttons appropriately
                        if (speed == 2) fast.turnOn();
                        else if (speed == 256) slow.turnOff();
                    }
                }

                // Reset
                else if (ev.keyboard.keycode == ALLEGRO_KEY_R ||
                         ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE ||
                         ev.keyboard.keycode == ALLEGRO_KEY_DELETE)
                    doReset(reset, pegs,
                            play, during, done,
                            height);

                // Peg num
                else if (ev.keyboard.keycode == ALLEGRO_KEY_3 &&
                         pegNum.isActive()) enter = true;

                // Theme chooser
                else if (ev.keyboard.keycode == ALLEGRO_KEY_T)
                    themeChoose = true;

                // Shuffle
                else if (ev.keyboard.keycode == ALLEGRO_KEY_S ||
                         ev.keyboard.keycode == ALLEGRO_KEY_SLASH)
                    doShuffler(shuffler, movedown, pegs,
                               height, during, done);

                // Night mode
                else if (ev.keyboard.keycode == ALLEGRO_KEY_N) {
                    doNight(night, textColor,
                            nightmode);
                }

            }

      	}

        al_flip_display();

	}

	al_destroy_display(display);

    return 0;

}

// Draw rings
void draw(int n, int pos, int height, int peg, int theme,
          const ALLEGRO_DISPLAY_MODE &disp_data) {

    // Calculate color
    vector<float> temp = rainbow(n, height, theme);

    al_draw_filled_rectangle((float)peg/4*disp_data.width-
                             (float)n/height*(disp_data.width/8-10)-10,
                             (2-(float)(pos+1)/(height+1))*
                             (disp_data.height/2-10)+10,
                             (float)peg/4*disp_data.width+
                             (float)n/height*(disp_data.width/8-10)+10,
                             (2-(float)pos/(height+1))*
                             (disp_data.height/2-10)+10,
                             al_map_rgb(temp[0],temp[1],temp[2]));

}

// Execute move
void execute(int nMove, Peg pegs[3]) {

    pegs[nMove%10].push(pegs[nMove/10].pop());

}

// Invert or reverse a move
int reverseMove(int m) {

    return m%10*10+m/10;

}

// Classic solve
vector<int> solve(int height, int peg1, int peg2) {

    vector<int> out, temp;
    // Base case
    if (height == 1)
        out.push_back(10*(peg1%3)+(peg2%3));
    else {
        // Recursive step
        temp = solve(height-1, peg1%3, 3-(peg1+peg2)%3);
        for (int i = 0; i < temp.size(); i++)
            out.push_back(temp[i]);
        out.push_back(10*(peg1%3)+(peg2%3));
        temp = solve(height-1, 3-(peg1+peg2)%3, peg2);
        for (int i = 0; i < temp.size(); i++)
            out.push_back(temp[i]);
    }

    return out;

}

// Find which peg a ring is on
int findRing(int pos, Peg pegs[3]) {

    int out = 0;

    if (pegs[1].hasInt(pos)) out = 1;
    else if (pegs[2].hasInt(pos)) out = 2;

    return out;

}

// Solve from arbitrary position
// Original algorithm (top up)
vector<int> solveArb(int height, Peg pegs[3]) {

    vector<int> out, temp;
    // Solve rings from smallest to largest
    for (int i = 1; i < height; i++) {
        if (findRing(i, pegs) != findRing(i+1, pegs)) {
            // Move solved rings to smallest unsolved ring
            temp = solve(i, findRing(i, pegs), findRing(i+1, pegs));
            for (int j = 0; j < temp.size(); j++)
                out.push_back(temp[j]);
        }
    }

    return out;

}

// Optimized algorithm (bottom up)
vector<int> solveArb2(int height, Peg pegs[3], int dest) {

    vector<int> out, temp, temp2;
    int p;
    // Solve rings largest to smallest
    for (int i = 0; i < height; i++) {
        p = findRing(height-i, pegs);
        // If not in place
        if (p != dest) {
            // If there is obstruction above ring
            if (!(pegs[p].getTop() == height-i &&
                  (!pegs[dest].getTop() ||
                   pegs[dest].getTop() > height-i))) {
                // Solve the rings to the third peg
                temp = solveArb2(height-i-1, pegs, 3-p-dest);
                for (int j = 0; j < temp.size(); j++) {
                    out.push_back(temp[j]);
                }
            }
            // Solve ring
            out.push_back(p*10+dest);
            // Solve the other rings
            if (height-i-1 > 0) {
                temp2 = solve(height-i-1, 3-p-dest, dest);
                for (int j = 0; j < temp2.size(); j++) {
                        out.push_back(temp2[j]);
                }
            }
            break;
        }
    }

    return out;

}

// Simplify solutions
vector<int> simplify(vector<int> sol) {

    bool change;
    do {
        change = false;
        for (int i = 0; i < sol.size() - 1; i++) {
            // Check for cancellation
            if (reverseMove(sol[i]) == sol[i+1]) {
                sol.erase(sol.begin()+i, sol.begin()+i+2);
                change = true;
                break;
            }
            // Check for move combining
            else if (sol[i]%10 == sol[i+1]/10) {
                sol[i] = sol[i]/10*10+sol[i+1]%10;
                sol.erase(sol.begin()+i+1);
                change = true;
                break;
            }
        }
    } while (change);

    return sol;

}

// Draw color themes
vector<float> rainbow(int pos, int height, int theme) {

    // Index based on place in tower
    float temp = (float)(pos-1)/max(height-1, 1);
    vector<float> out(3,0);

    // Halloween theme
    if (theme == 1) {
        // Gradient from orange to black
        out[0] = temp;
        out[1] = temp/2;

    }

    // Christmas theme
    else if (theme == 2) {
        // Alternating green and red
        if (pos % 2) {
            out[1] = 1;
        }
        else {
            out[0] = 1;
        }
    }

    // Easter theme
    else if (theme == 3) {
        // Gradient between 5 "Easter colors"
        if (temp <= 0.25) {
            out[0] = (float)253/255 - 12*temp/255;
            out[1] = (float)199/255 + 180*temp/255;
            out[2] = (float)199/255 - 192*temp/255;
        }
        else if (temp > 0.25 && temp <= 0.5) {
            out[0] = (float)250/255 - 628*(temp-0.25)/255;
            out[1] = (float)244/255 - 28*(temp-0.25)/255;
            out[2] = (float)151/255 + 112*(temp-0.25)/255;
        }
        else if (temp > 0.5 && temp <= 0.75) {
            out[0] = (float)93/255 - 28*(temp-0.5)/255;
            out[1] = (float)237/255 - 52*(temp-0.5)/255;
            out[2] = (float)179/255 + 152*(temp-0.5)/255;
        }
        else {
            out[0] = (float)86/255 + 344*(temp-0.75)/255;
            out[1] = (float)224/255 - 232*(temp-0.75)/255;
            out[2] = (float)217/255 - 88*(temp-0.75)/255;
        }
    }

    // Plain theme
    else if (theme == 4) {
        out[0] = DARKWOOD.r;
        out[1] = DARKWOOD.g;
        out[2] = DARKWOOD.b;
    }

    // Rainbow theme
    else {
        // Gradient between 7 rainbow colors
        if (temp <= (float)1/6) {
            out[0] = 1;
            out[1] = 3*temp;
        }
        else if (temp > (float)1/6 && temp <= (float)1/3) {
            out[0] = 1;
            out[1] = 3*temp;
        }
        else if (temp > (float)1/3 && temp <= 0.5) {
            out[0] = 3-6*temp;
            out[1] = 1;
        }
        else if (temp > 0.5 && temp <= (float)2/3) {
            out[1] = 1;
            out[2] = 6*temp-3;
        }
        else if (temp > (float)2/3 && temp <= (float)5/6) {
            out[0] = 0;
            out[1] = 5-6*temp;
            out[2] = 1;
        }
        else {
            out[0] = 3*temp-2.5;
            out[2] = 1;
        }
    }

    out[0] *= 255;
    out[1] *= 255;
    out[2] *= 255;

    return out;

}

// Functions to handle button actions

// Animate button
void doAnimate(Button &animate, Button &movedown, Button &moveup,
               Button &pegNum, Button &shuffler,
               bool &play, bool done, bool &during,
               int &moveCount, int height, int &solLen,
               Peg pegs[3], vector<int> &solution,
               const ALLEGRO_DISPLAY_MODE &disp_data,
               ALLEGRO_FONT *font) {

    // Split cases depending on if the animation is already running
    if (play) {

        play = false;
        animate.setText("RESUME");
        animate.setColor(GREEN);
        if (moveCount) movedown.turnOn();
        moveup.turnOn();
        pegNum.turnOn();
        shuffler.turnOn();

    }

    else {

        // Generate solution if appropriate
        if (!during && !done) {
            // Draw loading box
            al_draw_filled_rectangle(3*disp_data.width/7, 3*disp_data.height/7,
                                    4*disp_data.width/7, 4*disp_data.height/7,
                                    WHITE);
            al_draw_rectangle(3*disp_data.width/7, 3*disp_data.height/7,
                            4*disp_data.width/7, 4*disp_data.height/7,
                            BLACK, 1);

            al_draw_text(font, BLACK, disp_data.width/2, disp_data.height/2-10,
                         ALLEGRO_ALIGN_CENTER, "Loading...");
            al_flip_display();

            // Solution generation
            solution.clear();
            solution = solveArb2(height, pegs, findRing(height, pegs));
            moveCount = 0;
            solLen = solution.size();
        }

        // Modify variables
        during = true;
        play = true;
        animate.setText("PAUSE");
        animate.setColor(RED);
        movedown.turnOff();
        moveup.turnOff();
        pegNum.turnOff();
        shuffler.turnOff();

    }

}

// Move forward button
void doMoveup(const Button &moveup, Button &movedown,
              Peg pegs[3], bool &done, bool &during,
              int &moveCount, int &solLen, int height,
              vector<int> &solution,
              const ALLEGRO_DISPLAY_MODE &disp_data,
              ALLEGRO_FONT *font) {

    if (moveup.isActive()) {
        // Generate solution if appropriate
        if (!during && !done) {
            // Draw loading box
            al_draw_filled_rectangle(3*disp_data.width/7, 3*disp_data.height/7,
                                    4*disp_data.width/7, 4*disp_data.height/7,
                                    WHITE);
            al_draw_rectangle(3*disp_data.width/7, 3*disp_data.height/7,
                            4*disp_data.width/7, 4*disp_data.height/7,
                            BLACK, 1);
            al_draw_text(font, BLACK, disp_data.width/2, disp_data.height/2-10,
                         ALLEGRO_ALIGN_CENTER, "Loading...");
            al_flip_display();

            // Solution generation
            solution.clear();
            solution = solveArb2(height, pegs, findRing(height, pegs));
            moveCount = 0;
            solLen = solution.size();
        }

        // Modify variables
        execute(solution[moveCount], pegs);
        done = false;
        during = true;
        moveCount++;
        if (moveCount) movedown.turnOn();

    }

}

// Move backward button
void doMovedown(const Button &movedown, Peg pegs[3],
                int &moveCount, const vector<int> &solution) {

    // Do reverse move, modify moveCount
    if (movedown.isActive()) {
        execute(reverseMove(solution[moveCount-1]), pegs);
        moveCount--;
    }

}

// Reset button
void doReset(const Button &reset, Peg pegs[3],
             bool &play, bool &during, bool &done,
             int height) {

    if (reset.isActive()) {
        play = false;
        during = false;
        // Clear pegs
        for (int i = 0; i < 3; i++) pegs[i].toEmpty();
        for (int i = height; i > 0; i--) pegs[0].push(i);
        // Trigger new solution generation
        done = false;
    }

}

// Shuffle pegs (for shuffler button)
void shuffle(int height, Peg pegs[3]) {

    for (int i = 0; i < 3; i++) pegs[i].toEmpty();
    for (int i = height; i > 0; i--) {
        pegs[rand()%3].push(i);
    }

}

// Shuffler button
void doShuffler(const Button &shuffler, Button &movedown, Peg pegs[3],
                int height, bool &during, bool &done) {

    if (shuffler.isActive()) {
        shuffle(height, pegs);
        during = false;
        done = false;
        movedown.turnOff();
    }

}

// Night mode button
void doNight(Button &night, ALLEGRO_COLOR &textColor,
             bool &nightmode) {

    // Change colors, variables
    if (night.isActive()) {
        if (nightmode) {
            night.setColor(BLACK);
            night.setTColor(WHITE);
            textColor = BLACK;
        }
        else {
            night.setColor(WHITE);
            night.setTColor(BLACK);
            textColor = WHITE;
        }
        nightmode = !nightmode;
    }

}
