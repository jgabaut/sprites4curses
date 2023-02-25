#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "animate.h"

/*
 * Takes a string and a int and prints it in curses sdtscr at the y value passed as line_num.
 * @param line The string to print
 * @param line_num The y value to print at in std_scr
 */
static void print_spriteline(WINDOW* win, char* line, int line_num) {
    int color = -1;

    for (int i=0; i<18; i++) {
        char c = line[i];
        switch (c) {
            case '\n': {
                return;
            }
            case 'c': {
                color = CYAN;
                break;
            }
            case 'b': {
                color = BLUE;
                break;
            }
            case 'r': {
                color = RED;
                break;
            }
            case 'k': {
                color = BLACK;
                break;
            }
            case 'w': {
                color = WHITE;
                break;
            }
            case 'm': {
                color = MAGENTA;
                break;
            }
            case 'g': {
                color = GREEN;
                break;
            }
            case 'y': {
                color = YELLOW;
                break;
            }
        }
        wattron(win, COLOR_PAIR(color));
        mvwaddch(win, line_num, 1+i, ' '|A_REVERSE);
        wattroff(win, COLOR_PAIR(color));
    }
}

/* 
 * Takes a string and trims whitespace at the edges.
 * @param str The string to trim.
 * @return str The trimmed string.
 */
static char *trim(char *str) {
    char *end;

    // Trim leading whitespace
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // Trim trailing whitespace
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    // Add null terminator
    *(end+1) = '\0';

    return str;
}

/*
 * Takes an empty 3D char array (frame, height, width) and a file to read the sprites from.
 * File format should have a sprite line on each line.
 * Sets all the frames to the passed array.
 * @param sprites The char array to fill with all the frames.
 * @param f The file to read the sprites from.
 * @param rows The number of rows in each sprite.
 * @param columns The number of columns in each sprite.
 */
void load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], FILE* f, int rows, int columns) {

    char line[1024];
    char *token;
    int row = 0, frame = 0;

    while (fgets(line, sizeof(line), f)) {
        // Skip empty lines
        if (line[strspn(line, " \t\r\n")] == '\0') {
            continue;
        }

        // Skip comment lines
        if (line[strspn(line, " \t\r\n")] == '/') {
            continue;
        }

        // Skip the first line of the file
        if (frame == 0 && row == 0) {
            frame++;
            continue;
        }

        // Parse the line
        token = strtok(line, "\"");
        while (token != NULL) {
            if (token[0] != ',' && token[0] != '{' && token[0] != '}' && token[0] != '\t' && token[0] != '\n' && token[0] != '\"' && (token[0] != '}' && token[1] != ',' )) {
		strncpy(sprites[frame-1][row], token, columns);
		sprites[frame-1][row][columns] = '\0'; // add null-terminator to end of string

               // strcpy(sprites[frame-1][row], token);
                row++;
                if (row == rows) {
                    frame++;
                    row = 0;
                }
            }
            token = strtok(NULL, "\"");
        }
    }

    fclose(f);
}

/*
 * Initialises all the needed color pairs for curses.
 */
void init_s4c_color_pairs() {
    init_pair(RED, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
    init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}

/*
 * Takes a WINDOW pointer to print into and a string for the file passed.
 * Loads sprites from the file and displays them in the passed window if it is big enough.
 * File format should have a sprite line on each line, or be a valid array definition.
 * Color-character map is define in print_spriteline().
 * Sets all the frames to the passed array.
 * @see print_spriteline()
 * @param w The window to print into.
 * @param file The file to read the sprites from.
 * @param repetition The number of times the animation will be cycled through.
 * @param frametime How many mseconds each frame is displayed.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 */
void animate_file(WINDOW* w, FILE* file, int repetitions, int frametime, int num_frames, int frameheight, int framewidth) {

	int rows = frameheight;
	int cols = framewidth;	

	// Check if window is big enough
	int win_rows, win_cols;
	getmaxyx(w, win_rows, win_cols);
	if (win_rows < rows || win_cols < cols) {
		fprintf(stderr, "Window is too small to display the sprite\n");
		exit(EXIT_FAILURE);
	}

    	// Prepare the frames
	char sprites[MAXFRAMES][MAXROWS][MAXCOLS]; 
	load_sprites(sprites, file, rows-1, cols-1);

	int r = 0;
   	// Run the animation loop
   	while ( r < repetitions ) {
		for (int i=0; i<num_frames+1;i++) {
			for (int j=0; j<rows; j++) {
				// Print current frame
				print_spriteline(w,sprites[i][j], j+1);
				box(w,0,0);
				wrefresh(w);
			}
			wrefresh(w);
			// Refresh the screen
			napms(frametime);
			move(0,0);
			clear();
		};      	
		r++;
		if (r==repetitions) {
			break;
		}
	}
}

