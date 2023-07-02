#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include "../s4c-animate/animate.h"

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
 * Demo function showing how to call s4c-animate functions correctly.
 * It initialises a window pointer and all needed curses settings, before calling the animation functions.
 * @see init_color_pairs()
 * @see animate_file()
 * @return Result of the animation.
 */
int demo(FILE* mainthread_file, FILE* newthread_file) {

	printf("\n\n\t\tDEMO for ");
	S4C_PRINTVERSION();
	printf("\n\n\t\tShows how to correctly call animate functions.h\n");
	printf("\n\t\t[Press Enter to start the demo]\n");
	scanf("%*c");
	system("clear");

	// Open the palette file to read the color values and name
	// Keep in mind that the file pointer will be closed by init_s4c_color_pairs(palette_file);
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

	// Initialisation: we need a large enough window and all the curses settings needed to be applied before calling animate_sprites().
	WINDOW* w;
	setlocale(LC_CTYPE, "it_IT.UTF-8");
	initscr();
	clear();
	refresh();
	start_color();
	int colorCheck = has_colors();

	if (colorCheck == FALSE	) {
		fprintf(stderr,"Terminal can't use colors, abort.\n");
		return S4C_ERR_TERMCOLOR;
	}

	colorCheck = can_change_color();

	if (colorCheck == FALSE	) {
		fprintf(stderr,"Terminal can't change colors, abort.\n");
		return S4C_ERR_TERMCHANGECOLOR;
	}
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	// Initialize all the colors using the palette file we opened at the start
	init_s4c_color_pairs(palette_file);

	int reps = 1;
	int frametime = DEMOFRAMETIME;
	int num_frames = DEMOFRAMES;
	int frame_height = DEMOROWS;
	int frame_width = DEMOCOLS;

	// Window must be big enough to fit the animation AND the boxing of the window.
	// The boxing done by animate is 1 pixel thick. In this demo, we also add extra space to show that you can print at any coords with the at_coords function.
	w = newwin(frame_height + 1 +2, frame_width + 1 +3, 0, 20);

	// Prepare the frames
	char sprites[MAXFRAMES][MAXROWS][MAXCOLS];
	int loadCheck = load_sprites(sprites, mainthread_file, frame_height-1, frame_width-1);

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
	wrefresh(w);

	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Let's see animate_sprites:");
	mvwprintw(stdscr,4,2, "This function puts the Upper Left animation corner at (0,0).");
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(w);
	// Then we call the animation function with all the needed arguments

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
	wrefresh(w);
	int try_x = 1;
	int try_y = 1;
	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Now animate_sprites_at_coords:");
	mvwprintw(stdscr,4,2, "This function puts UL animation corner at (y:%i,x:%i).", try_y, try_x);
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	// We call the animation to be displayed at 3,3
	result = animate_sprites_at_coords(sprites, w, reps, frametime, num_frames, frame_height, frame_width, try_y, try_x);
	// We should check animate_sprites_at_coords() result to see if there were problems, but in the demo we don't expect problems so we ignore the specific error content of result and just exit.

	if (result < 0) {
		endwin();
		fprintf(stderr,"Demo error while doing animate_sprites_at_coords()");
		exit(EXIT_FAILURE);
	}


	// We clear the window, and expect animate__() to refresh it
	wclear(w);
	wrefresh(w);
	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Now animate_rangeof_sprites_at_coords, using a frame range of (10-20), including 20th frame:");
	mvwprintw(stdscr,4,2, "This function puts the requested frames of UL animation corner at (y:%i,x:%i).", try_y, try_x);
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	// We call the animation to be displayed at 3,3
	result = animate_rangeof_sprites_at_coords(sprites, w, 10, 20, reps, frametime*3, num_frames, frame_height, frame_width, try_y, try_x);
	// We should check animate_sprites_at_coords() result to see if there were problems, but in the demo we don't expect problems so we ignore the specific error content of result and just exit.

	if (result < 0) {
		endwin();
		fprintf(stderr,"Demo error while doing animate_rangeof_sprites_at_coords()");
		exit(EXIT_FAILURE);
	}

	wclear(w);
	wrefresh(w);

	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Now animate_sprites_thread_at, we ask for a new thread.");
	mvwprintw(stdscr,4,2, "UL animation corner will be at (y:%i,x:%i).", try_y, try_x);
	mvwprintw(stdscr,5,2, "Animation will loop until you press Enter on that screen.");
	mvwprintw(stdscr,7,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	pthread_mutex_t animation_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t animation_cond = PTHREAD_COND_INITIALIZER;
	animate_args* animation_thread_args = (animate_args*) malloc(sizeof(animate_args));
	pthread_t animation_thread;

	int stop_animation=0;

	animation_thread_args->frametime = frametime;

	animation_thread_args->num_frames = num_frames;

	animation_thread_args->frameheight = frame_height;
	animation_thread_args->framewidth = frame_width;
	animation_thread_args->startX = try_x;
	animation_thread_args->startY = try_y;

	//We load the sprites to animation_thread_args
	loadCheck = load_sprites(animation_thread_args->sprites, newthread_file, animation_thread_args->frameheight-1, animation_thread_args->framewidth-1);

	//We check if the loading went ok

	// Start animation thread
	animation_thread_args->win = w;
	animation_thread_args->stop_thread = stop_animation;
	pthread_create(&animation_thread, NULL, animate_sprites_thread_at, animation_thread_args);
	refresh();

	//Wait for enter to stop animation
	scanf("%*c");
	stop_animation=1;

	// Stop the animation
	pthread_mutex_lock(&animation_mutex);
	animation_thread_args->stop_thread = stop_animation;
	pthread_cond_signal(&animation_cond);
	// Wait for the animation thread to finish
	pthread_join(animation_thread, NULL);
	pthread_mutex_unlock(&animation_mutex);

	//Free animation thread arguments and end demo
	free(animation_thread_args);
	endwin();

	clear();
	refresh();
	printf("\n\n\t\tEnd of demo.");
	printf("\n\t\t[Press Enter to end the demo]\n");
	scanf("%*c");
	system("clear");

	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		usage(argv[0]);
	}

    	FILE *f = fopen(argv[1], "r");
    	FILE *f2 = fopen(argv[1], "r");
    	if (!f) {
        	fprintf(stderr,"Error opening file %s as f1.\n",argv[1]);
		usage(argv[0]);
    	}
    	if (!f2) {
        	fprintf(stderr,"Error opening file %s as f2.\n",argv[1]);
		usage(argv[0]);
    	}
	int result = demo(f,f2);
	//Since we passed f and f2 to load_sprites(), each one was already closed in that call after the sprites had been set

	return result;
}
