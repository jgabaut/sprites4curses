#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "animate.h"

static color_pair_t S4C_COLOR_PAIRS[MAX_COLORS];

/*
 * Initialises all the needed color pairs for animate, from the palette file. WIP.
 */
static void init_color_pairs_from_palette() {
    // Open the palette file and read the color values and names
    FILE* fp;
    fp = fopen("palette.gpl", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open palette file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int color_index = 1;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        // Check if the line starts with "#", "GIMP Palette", "Name:" or "Columns:"
        if (strncmp(line, "#", 1) == 0 || strncmp(line, "GIMP Palette", 12) == 0 ||
            strncmp(line, "Name:", 5) == 0 || strncmp(line, "Columns:", 8) == 0) {
            // Skip the comment or irrelevant line
            continue;
        }

        // Parse the color values and name
        int r, g, b;
        char name[MAX_COLOR_NAME_LEN];
        if (sscanf(line, "%d %d %d %[^\n]", &r, &g, &b, name) != 4) {
            fprintf(stderr, "Error: could not parse palette line: %s\n", line);
            continue;
        }

        // Add the color pair to the COLOR_PAIRS array
        S4C_COLOR_PAIRS[color_index-1].fg = color_index-1;
        if (color_index-1 == BLACK) {
            S4C_COLOR_PAIRS[color_index-1].bg = WHITE;
        } else { 
            S4C_COLOR_PAIRS[color_index-1].bg = BLACK;
        }
        strncpy(S4C_COLOR_PAIRS[color_index-1].name, name, MAX_COLOR_NAME_LEN - 1);
        color_index++;
    }

    fclose(fp);

    // Initialize the color pairs in curses
    for (int i = 0; i < color_index+1; i++) {
        init_pair(i, S4C_COLOR_PAIRS[i].fg, S4C_COLOR_PAIRS[i].bg);
    }
}

/*
 * Takes a string and a int and prints it in curses sdtscr at the y value passed as line_num.
 * @param line The string to print
 * @param line_num The y value to print at in win
 * @param line_len The length of line to print
 */
static void print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length) {
    for (int i = 0; i < line_length; i++) {
        char c = line[i];
        int color_index = c - 'a';
        if (color_index >= 0 && color_index < MAX_COLORS) {
            wattron(win, COLOR_PAIR(color_index));
            mvwaddch(win, curr_line_num, 1 + i, ' ' | A_REVERSE);
            wattroff(win, COLOR_PAIR(color_index));
        }
        
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
	// We make the cursor invisible
	curs_set(0);
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
				print_spriteline(w,sprites[i][j], j+1, cols);
				box(w,0,0);
				wrefresh(w);
			}
			wrefresh(w);
			// Refresh the screen
			napms(frametime);
			clear();
		};      	
		r++;
	}
	// We make the cursor normal again
	curs_set(1);
}

