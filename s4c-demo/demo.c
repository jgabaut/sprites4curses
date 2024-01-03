// jgabaut @ github.com/jgabaut
// SPDX-License-Identifier: GPL-3.0-only
/*
    Copyright (C) 2023  jgabaut

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 3 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <unistd.h>
#include <stdlib.h>
#include <locale.h>
#include "../s4c-animate/animate.h"
#include "../s4c-animate/palette.h"

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

typedef enum Screen { LOGO = 0, GAMEPLAY, ENDING } Screen;

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
#ifdef S4C_RAYLIB_EXTENSION
    printf("\n\n\t\tRaylib extension enabled\n");
#endif
#ifdef S4C_EXPERIMENTAL
    printf("\n\n\t\tExperimental extension enabled\n");
#endif

    int drop_res = -1;
#ifndef S4C_RAYLIB_EXTENSION
	printf("\n\t\t[Press Enter to start the demo]\n");
	drop_res = scanf("%*c");
#ifndef _WIN32
	drop_res = system("clear");
#else
	drop_res = system("cls");
#endif

	printf("\n\n\t\tShows debug output for the provided S4C_Color array, defined in the generated \"palette.c\" file.\n");
	printf("\n\t\t[Press Enter to continue]\n");
	drop_res = scanf("%*c");
	drop_res = system("clear");
	for (int i = 0; i < PALETTE_S4C_H_TOTCOLORS; i++) {
		debug_s4c_color(&palette[i]);
	}
	printf("\n\t\t[Press Enter to continue]\n");
	drop_res = scanf("%*c");
	drop_res = system("clear");


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
	int frametime = DEMOFRAMETIME;
#endif

	int num_frames = DEMOFRAMES;
	int frame_height = DEMOROWS;
	int frame_width = DEMOCOLS;

#ifndef S4C_RAYLIB_EXTENSION

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


	// HINT:
	// Initialize all the colors using the palette.gpl file we opened at the start
	//init_s4c_color_pairs(palette_file);

	// Initialize all the colors using the generated palette.h file
	for (int i = 0; i < PALETTE_S4C_H_TOTCOLORS; i++) {
		init_s4c_color_pair(&palette[i],9+i);
	}

	int reps = 1;

	// Window must be big enough to fit the animation AND the boxing of the window.
	// The boxing done by animate is 1 pixel thick. In this demo, we also add extra space to show that you can print at any coords with the at_coords function.
	w = newwin(frame_height + 1 +2, frame_width + 1 +3, 0, 20);

#endif

	// Prepare the frames
	char sprites[MAXFRAMES][MAXROWS][MAXCOLS];
	int loadCheck = s4c_load_sprites(sprites, mainthread_file, num_frames, frame_height-1, frame_width-1);

	// Check for possible loadCheck() errors and in this case we return early if we couldn't load
	if (loadCheck < 0) {
#ifndef S4C_RAYLIB_EXTENSION
		endwin();
#endif
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

#ifndef S4C_RAYLIB_EXTENSION

	// We make sure we have the background correcly set up and expect animate_sprites to refresh it
	wclear(w);
	wrefresh(w);

	mvwprintw(stdscr,5,20, "Loaded [%i] frames.",loadCheck);
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");

	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Let's see a demo of the colors supported by the provided palette.gpl file:");
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
	// Then we call the demo function with all the needed arguments
	test_s4c_color_pairs(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	mvwprintw(stdscr,3,2, "Let's see a slideshow of the colors:");
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	mvwprintw(stdscr,8,20, "[Press \"<-\"  \"->\" to scroll colors]");
	mvwprintw(stdscr,9,20, "[Press Enter or q to end the slideshow]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
	// Then we call the slideshow function with all the needed arguments
	noecho();
	slideshow_s4c_color_pairs(stdscr);
	echo();
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
    int result = -1;

#ifdef S4C_EXPERIMENTAL
	S4C_Animation* animation = malloc(sizeof(S4C_Animation));

	s4c_copy_animation_alloc(animation,sprites,DEMOFRAMES,DEMOROWS,DEMOCOLS);

	int test_x = 1;
	int test_y = 1;

	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Let's see s4c_display_frame():");
	mvwprintw(stdscr,4,2, "This function puts the Upper Left animation corner at (%i,%i).",test_x,test_y);
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(w);
	// Then we call the animation function with all the needed arguments

	result = s4c_display_frame(animation, 3, w, DEMOFRAMES, DEMOROWS, DEMOCOLS, test_x, test_y);

	mvwprintw(stdscr,6,20, "[Press Enter to continue] (And free the allocated animation.)");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(w);


	//We can free the dinamic animation as the rest of the demo won't use it.
	//NEVER forget to free the dinamic animations you use.

	s4c_free_animation(animation, DEMOFRAMES, DEMOROWS);

	// We check s4c_display_frame() result to see if there were problems:
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

	wclear(stdscr);
	wrefresh(stdscr);
#endif

	mvwprintw(stdscr,3,2, "Let's see animate_sprites:");
	mvwprintw(stdscr,4,2, "This function puts the Upper Left animation corner at (0,0).");
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);
	wclear(w);
	// Then we call the animation function with all the needed arguments

	result = s4c_animate_sprites(sprites, w, reps, frametime, num_frames, frame_height, frame_width);

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
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	// We call the animation to be displayed at 3,3
	result = s4c_animate_sprites_at_coords(sprites, w, reps, frametime, num_frames, frame_height, frame_width, try_y, try_x);
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
	mvwprintw(stdscr,3,2, "Now display_sprite_at_coords, using frame index 13:");
	mvwprintw(stdscr,4,2, "This function puts the requested frame of UL animation corner at (y:%i,x:%i).", try_y, try_x);
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	// We call the animation to be displayed at 3,3
	result = s4c_display_sprite_at_coords(sprites, 13, w, num_frames, frame_height, frame_width, try_y, try_x);
	// We should check animate_sprites_at_coords() result to see if there were problems, but in the demo we don't expect problems so we ignore the specific error content of result and just exit.

	if (result < 0) {
		endwin();
		fprintf(stderr,"Demo error while doing display_sprite_at_coords()");
		exit(EXIT_FAILURE);
	}

	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	wclear(w);
	wrefresh(w);

	wclear(stdscr);
	wrefresh(stdscr);

	// We clear the window, and expect animate__() to refresh it
	wclear(w);
	wrefresh(w);
	wclear(stdscr);
	wrefresh(stdscr);
	mvwprintw(stdscr,3,2, "Now animate_rangeof_sprites_at_coords, using a frame range of (10-20), including 20th frame:");
	mvwprintw(stdscr,4,2, "This function puts the requested frames of UL animation corner at (y:%i,x:%i).", try_y, try_x);
	mvwprintw(stdscr,6,20, "[Press Enter to continue]");
	wrefresh(stdscr);
	drop_res = scanf("%*c");
	wclear(stdscr);
	wrefresh(stdscr);

	// We call the animation to be displayed at 3,3
	result = s4c_animate_rangeof_sprites_at_coords(sprites, w, 10, 20, reps, frametime*3, num_frames, frame_height, frame_width, try_y, try_x);
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
	drop_res = scanf("%*c");
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
	loadCheck = s4c_load_sprites(animation_thread_args->sprites, newthread_file, animation_thread_args->num_frames, animation_thread_args->frameheight-1, animation_thread_args->framewidth-1);
	//We check if the loading went ok

	// Start animation thread
	animation_thread_args->win = w;
	animation_thread_args->stop_thread = stop_animation;
	pthread_create(&animation_thread, NULL, s4c_animate_sprites_thread_at, animation_thread_args);
	refresh();

	//Wait for enter to stop animation
	drop_res = scanf("%*c");
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

	clear();
	refresh();
	endwin();
#else
    int screenWidth = 800;
    int screenHeight = 450;
    int logo_sleep = 120;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(screenWidth, screenHeight, "S4C Raylib test");

    Screen currentScreen = LOGO;

    // TODO: Initialize all required variables and load all required data here!
    int framesCounter = 0;          // Useful to count frames
    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    int current_anim_frame = 0;
    S4C_Sprite curr_sprite = s4c_new_sprite(sprites[current_anim_frame], 17, 17, palette, PALETTE_S4C_H_TOTCOLORS);

    while (!WindowShouldClose()) {
        // Update
        //----------------------------------------------------------------------------------
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        switch(currentScreen)
        {
            case LOGO:
            {
                // TODO: Update LOGO screen variables here!

                framesCounter++;    // Count frames
                // Wait for logo_sleep frames before jumping to GAMEPLAY screen
                if (framesCounter % logo_sleep == 0)
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!
                framesCounter++;    // Count frames
                if (framesCounter % 2 == 0)
                {
                    current_anim_frame = ( current_anim_frame < num_frames-1 ? current_anim_frame +1 : 0);
                    curr_sprite = s4c_new_sprite(sprites[current_anim_frame], 17, 17, palette, PALETTE_S4C_H_TOTCOLORS);
                }
                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = ENDING;
                }
            } break;
            case ENDING:
            {
                // TODO: Update ENDING screen variables here!
                // Press enter to return to LOGO screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = LOGO;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("Using s4c-animate v" S4C_ANIMATE_VERSION, 250, 250, 20, BLACK);
                    DrawText("Using raylib v" RAYLIB_VERSION, 250, 280, 20, BLACK);
                    DrawText("WAIT for 2 SECONDs...", 290, 220, 20, GRAY);
                } break;
                case GAMEPLAY:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    Rectangle r = CLITERAL(Rectangle){0, 0, screenWidth, screenHeight};
                    DrawRectangleRec(r, RAYWHITE);
                    //int res = s4rl_draw_sprite_at_rect(sprites[current_anim_frame], r, 17, 17, 24, palette, PALETTE_S4C_H_TOTCOLORS);
                    int res = s4rl_draw_s4c_sprite_at_rect(curr_sprite, r, 24);
                    if (res != 0) {
                        fprintf(stderr,"%s():    Failed s4rl_draw_s4c_sprite_at_rect().\n", __func__);
                    }
                } break;
                case ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("End of demo for s4c-animate v" S4C_ANIMATE_VERSION ", raylib extension", 20, 120, 28, BLACK);
                    DrawText("PRESS ENTER or TAP to RETURN to LOGO SCREEN", 120, 220, 20, DARKBLUE);
                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    CloseWindow();
    return 0;
#endif
	printf("\n\n\t\tEnd of demo.");
	printf("\n\t\t[Press Enter to end the demo]\n");
	drop_res = scanf("%*c");
	drop_res = system("clear");

	return drop_res;
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
