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
 * @return Result of the animation.
 */
int demo(FILE* file) {

	// Initialisation: we need a large enough window and all the curses settings needed
	// to be applied before calling animate_file().
	WINDOW* w;

	// Initialize curses
	setlocale(LC_CTYPE, "it_IT.UTF-8");
	initscr();
	clear();
	refresh();
	start_color();
	int colorCheck = has_colors();

	if (colorCheck == FALSE	) {
		fprintf(stderr,"Terminal can't use colors, abort.\n");
		return S4C_ERR_TERMCOLOR;
	};

	colorCheck = can_change_color();

	if (colorCheck == FALSE	) {
		fprintf(stderr,"Terminal can't change colors, abort.\n");
		return S4C_ERR_TERMCHANGECOLOR;
	};
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

    	// Open the palette file and read the color values and name
	//
	// This must be done everytime the color definitions are reset.
	// See: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/color.html#COLORBASICS
	// Curses initializes all the colors supported by terminal when start_color() is called.
    	FILE* palette_file;
    	palette_file = fopen("palette.gpl", "r");
    	if (palette_file == NULL) {
        	fprintf(stderr, "Error: could not open palette file.\n");
       		return -1;
    	}

	// Initialize all the colors using the palette file
	init_s4c_color_pairs(palette_file);

	int reps = 1;

	int frametime = DEMOFRAMETIME;

	int num_frames = DEMOFRAMES;

	int frame_height = DEMOROWS;

	int frame_width = DEMOCOLS;

	// Window must be big enough to fit the animation AND the boxing of the window.
	// The boxing done by animate is 1 pixel thick.
	// In this demo, we also add extra space to show that you can print at any coords with the at_coords function.
	w = newwin(frame_height + 1 +2, frame_width + 1 +3, 2, 2);

	// Prepare the frames
	char sprites[MAXFRAMES][MAXROWS][MAXCOLS];
	int loadCheck = load_sprites(sprites, file, frame_height-1, frame_width-1);

	// Check for possible loadCheck() errors and in this case we return early if we couldn't load
	if (loadCheck < 0) {
		endwin();
		switch (loadCheck) {
			case S4C_ERR_FILEVERSION: {
        			fprintf(stderr,"S4C_ERR_FILEVERSION : Failed file version check.\n");
			}
			break;
			case S4C_ERR_LOADSPRITES: {
        			fprintf(stderr,"S4C_ERR_LOADSPRITES : Failed loading the sprites.\n");
			}
			break;
		}
		return loadCheck;
	}

	// We make sure we have the background correcly set up and expect animate_sprites to refresh it
	wclear(w);

	// We call the animation function with all the needed arguments

	int result = animate_sprites(sprites, w, reps, frametime, num_frames, frame_height, frame_width);

	// We check animate_sprites() result to see if there were problems:
	if (result < 0) {
		endwin();
		switch (result) {
			case S4C_ERR_SMALL_WIN: {
        			fprintf(stderr,"animate => S4C_ERR_SMALL_WIN : Window was too small.\n");
			}
			break;
			case S4C_ERR_LOADSPRITES: {
        			fprintf(stderr,"animate => S4C_ERR_LOADSPRITES : Failed loading the sprites.\n");
			}
			break;
			case S4C_ERR_FILEVERSION: {
        			fprintf(stderr,"animate => S4C_ERR_FILEVERSION : Failed file version check.\n");
			}
			break;
			case S4C_ERR_CURSOR: {
        			fprintf(stderr,"animate => S4C_ERR_CURSOR : Failed to change the cursor.\n");
			}
			break;
		}
	}

	// We clear the window, and expect animate__() to refresh it
	wclear(w);

	// We call the animation to be displayed at 3,3

	result = animate_sprites_at_coords(sprites, w, reps, frametime, num_frames, frame_height, frame_width, 1, 1);
	endwin();

	// We check animate_sprites_at_coords() result to see if there were problems:
	if (result < 0) {
		switch (result) {
			case S4C_ERR_SMALL_WIN: {
        			fprintf(stderr,"animate => S4C_ERR_SMALL_WIN : Window was too small.\n");
			}
			break;
			case S4C_ERR_LOADSPRITES: {
        			fprintf(stderr,"animate => S4C_ERR_LOADSPRITES : Failed loading the sprites.\n");
			}
			break;
			case S4C_ERR_FILEVERSION: {
        			fprintf(stderr,"animate => S4C_ERR_FILEVERSION : Failed file version check.\n");
			}
			break;
			case S4C_ERR_CURSOR: {
        			fprintf(stderr,"animate => S4C_ERR_CURSOR : Failed to change the cursor.\n");
			}
			break;
		}
	}

	return result;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		usage(argv[0]);
	}
    	FILE *f = fopen(argv[1], "r");
    	if (!f) {
        	fprintf(stderr,"Error opening file %s\n",argv[1]);
		usage(argv[0]);
    	}
	return demo(f);
}
