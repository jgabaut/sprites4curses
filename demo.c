#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include "animate.h"

#define DEMOFRAMES 30 /**< Defines the number of sprites in the demo.*/
#define DEMOROWS 18 /**< Defines the maximum number of rows per sprite.*/
#define DEMOCOLS 18 /**< Defines the maximum number of colums per sprite.*/
#define DEMOFRAMETIME 67 /**< Defines for how many millisecs a sprite should stay on screen in the demo.*/

/*
 * Prints correct invocation arguments for the demo and exits.
 * @param progname The program's name.
 */
void usage(char* progname) {
    fprintf(stderr,"Usage: %s <animation_file.txt>\n",progname);
    exit(EXIT_FAILURE);
}

/*
 * Demo function showing how to call animate_file() correctly.
 * It initialises a window pointer and all needed curses settings, before callin animate_file().
 * @see init_color_pairs()
 * @see animate_file()
 */
void demo(char* filename) {

	// Initialisation: we need a large enough window and all the curses settings needed
	// to be applied before calling animate_file().
	WINDOW* w;

	// Initialize curses
	setlocale(LC_CTYPE, "it_IT.UTF-8");
	initscr();
	clear();
	refresh();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// Initialize all the colors
	init_s4c_color_pairs();

	int reps = 5;

	int frametime = DEMOFRAMETIME;

	int num_frames = DEMOFRAMES;

	int frame_height = DEMOROWS;

	int frame_width = DEMOCOLS;
	
	// Window must be big enough to fit the animation AND the boxing of the window.
	w = newwin(frame_height+1, frame_width+1, 2, 2);

	animate_file(w, filename, reps, frametime, num_frames, frame_height, frame_width);
	endwin();
}

int main(int argc, char** argv) {
	if (argc != 2) {
		usage(argv[0]);
	}
	demo(argv[1]);
	return 0;
}
