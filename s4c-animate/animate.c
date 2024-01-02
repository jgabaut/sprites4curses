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

#include "animate.h"

/**
 * Prints formatted animate version.
 */
void s4c_printVersionToFile(FILE* f) {
	if (!f) {
		fprintf(stderr,"Error while trying to print formatted s4c version, invalid file pointer.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(f,"sprites4curses/animate.h v%s\n",S4C_ANIMATE_VERSION);
}

/**
 * Prints animate version.
 */
void s4c_echoVersionToFile(FILE* f) {
	if (!f) {
		fprintf(stderr,"Error while trying to print s4c version, invalid file pointer.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(f,"%s\n",S4C_ANIMATE_VERSION);
}

/**
 * Takes a S4C_Color pointer and a FILE pointer to print to.
 *
 * @param color The color to debug.
 * @param fp The file to debug to.
 */
void debug_s4c_color_2file(S4C_Color* color, FILE* fp) {
	if (!fp) {
		fprintf(stderr,"Error while trying to debug an S4C_Color, invalid file pointer.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(fp,"[S4C_Color] => { red: [%i], green: [%i], blue: [%i], name: [%s] }\n", color->red, color->green, color->blue, color->name);
}

/**
 * Takes a S4C_Color pointer and prints it to stdout.
 *
 * @param color The color to debug.
 */
void debug_s4c_color(S4C_Color* color) {
	debug_s4c_color_2file(color,stdout);
}

#ifndef S4RAYLIB_BUILD

/**
 * Initialises a color pair from a passed S4C_Color pointer.
 * @param palette The S4C_Color pointer array at hand.
 * @param color_index The resulting color index for defined colorpair.
 */
void init_s4c_color_pair(S4C_Color* color, int color_index) {

	if (color == NULL) {
		fprintf(stderr,"Error: invalid S4C_Color at %s().",__func__);
		exit(EXIT_FAILURE);
	}

        int r, g, b;
	char color_name[50];

	r = color->red;
	g = color->green;
	b = color->blue;
	strcpy(color_name,color->name);

	int proportional_r = (((float)r + 1.0) / 256)*1000;
	int proportional_g = (((float)g + 1.0) / 256)*1000;
	int proportional_b = (((float)b + 1.0) / 256)*1000;
	init_color(color_index, proportional_r, proportional_g, proportional_b);
   	init_pair(color_index, color_index, 0);
}
#endif

const char* s4c_color_strings[S4C_MAX_COLOR_INDEX+1] = {
	"S4C_BLACK",
	"S4C_RED",
	"S4C_BRIGHT_GREEN",
	"S4C_BRIGHT_YELLOW",
	"S4C_BLUE",
	"S4C_MAGENTA",
	"S4C_CYAN",
	"S4C_WHITE",
	"S4C_ORANGE",
	"S4C_LIGHT_BROWN",
	"S4C_DARK_BROWN",
	"S4C_PURPLE",
	"S4C_DARK_GREEN",
	"S4C_GREY",
	"S4C_LIGHT_YELLOW",
	"S4C_LIGHT_BLUE",
	"S4C_DARK_YELLOW",
	"S4C_DARK_OLIVE",
	"S4C_LIGHT_OLIVE",
	"S4C_OLIVE",
	"S4C_DARK_CHERRY",
	"S4C_LIGHT_CHERRY",
	"S4C_CHERRY",
	"S4C_SALMON",
	"S4C_DARK_BLUE",
	"S4C_VIOLET",
	"S4C_INDIGO",
	"S4C_LIGHT_ORANGE",
	"S4C_TEAL",
	"S4C_DARK_CYAN",
	"S4C_DARK_PURPLE",
	"S4C_LIGHT_PURPLE",
};

const char* s4c_color_name(S4C_Color_Index color_index) {
	if (color_index < S4C_MIN_COLOR_INDEX || color_index > S4C_MAX_COLOR_INDEX) {
		fprintf(stderr,"[%s]:  Invalid color index { %i }, { %s -> [%i] }.", __func__, color_index, (color_index < S4C_MIN_COLOR_INDEX ? "Below min valid value " : "Above max valid value"), (color_index < S4C_MIN_COLOR_INDEX ? S4C_MIN_COLOR_INDEX : S4C_MAX_COLOR_INDEX));
		abort();
	}
	return s4c_color_strings[color_index-S4C_MIN_COLOR_INDEX];
}

#ifndef S4RAYLIB_BUILD
/**
 * Initialises all the needed color pairs for animate, from the palette file.
 * @param palette The palette file to read the colors from.
 */
void init_s4c_color_pairs(FILE* palette) {

    char line[MAX_LINE_LENGTH];
    int color_index = 9;

    while (fgets(line, MAX_LINE_LENGTH, palette) != NULL) {
        // Check if the line starts with "#", "GIMP Palette", "Name:" or "Columns:"
        if (strncmp(line, "#", 1) == 0 || strncmp(line, "GIMP Palette", 12) == 0 ||
            strncmp(line, "Name:", 5) == 0 || strncmp(line, "Columns:", 8) == 0) {
            // Skip the comment or irrelevant line
            continue;
        }

        // Parse the color values and name
        int r, g, b;
        char name[S4C_PALETTEFILE_MAX_COLOR_NAME_LEN];
        if (sscanf(line, "%d %d %d %[^\n]", &r, &g, &b, name) != 4) {
            fprintf(stderr, "[%s]  Error: could not parse palette line: %s\n", __func__, line);
	    continue;
        }

	int proportional_r = (((float)r + 1.0) / 256)*1000;
	int proportional_g = (((float)g + 1.0) / 256)*1000;
	int proportional_b = (((float)b + 1.0) / 256)*1000;
	init_color(color_index, proportional_r, proportional_g, proportional_b);
   	init_pair(color_index, color_index, 0);

        color_index++;
    }

    //We close the palette file ourselves
    fclose(palette);
}

/**
 * Demoes all colors supported by the palette in the passed WINDOW. Not guaranteed to work.
 * Since it uses indexes defined by default from animate.h, it should work only when your currently initialised palette has color pairs for the expected index range.
 * @param win The window to print the demo to.
 */
void test_s4c_color_pairs(WINDOW* win) {
    for (int i = S4C_MIN_COLOR_INDEX; i < S4C_MAX_COLOR_INDEX +1; i++) {
        int color_index = i;
        if (color_index >= 0 && color_index < MAX_COLORS) {
            wattron(win, COLOR_PAIR(color_index));
            mvwaddch(win, 2, 2+i-S4C_MIN_COLOR_INDEX, ' ' | A_REVERSE);
            wattroff(win, COLOR_PAIR(color_index));
        }
    }

    wrefresh(win);
    refresh();
}

/**
 * Demoes color pairs defined in s4c to the passed window.
 * Since it uses indexes defined by default from animate.h, it should work only when your currently initialised palette has color pairs for the expected index range.
 * @param win The Window pointer to print to.
 * @param colors_per_row How many colors to print in each row.
 */
void slideshow_s4c_color_pairs(WINDOW* win) {
	if (win == NULL) {
		fprintf(stderr,"[%s]:  Passed Window was NULL.",__func__);
		abort();
	}
	int cursorCheck = curs_set(0); // We try making the cursor invisible

	if (cursorCheck == ERR) {
		//TODO
		//Log this
		//fprintf(stderr,"animate => Terminal does not support cursor visibility state.\n");
	}

	// Get window max size
	int win_rows, win_cols;
	getmaxyx(win, win_rows, win_cols);

	int picked = 0;
	int quit = 0;
	int c = -1;
	wrefresh(win);
	refresh();

	int color_index = S4C_MIN_COLOR_INDEX;

	do {
        	if (color_index >= 0) {
			wattron(win,COLOR_PAIR(color_index));
			for (int i=0; i<win_rows; i++) {
				for (int j=0; j<win_cols; j++) {
            				mvwaddch(win, i, j, ' ' | A_REVERSE);
				}
			}
			wattroff(win,COLOR_PAIR(color_index));
			if (win_cols > S4C_MAX_COLOR_NAME_LEN+9) {
				mvwprintw(win, 2, 1, "[%i] [%s]", color_index, s4c_color_name(color_index));
			} else if (win_cols > 5) {
				mvwprintw(win, 1, 1, "[%i]", color_index);
			}
			box(win,0,0);
			wrefresh(win);
			refresh();
		}
		c = wgetch(win);
		switch(c) {
			case 'q': { /*Enter*/
				quit = 1;

			};
			case 10: { /*Enter*/
				picked = 1;
			};
			break;
			case KEY_RIGHT: {
					color_index = (color_index == S4C_MAX_COLOR_INDEX ? color_index : color_index+1);

			};
			break;
			case KEY_LEFT: {
					color_index = (color_index == S4C_MIN_COLOR_INDEX ? color_index : color_index-1);

			};
			break;
			default: {
				//fprintf(stderr,"[%s]:  Unexpected int [%i].\n",__func__,c);
			}
			break;
		}
	} while(!quit && !picked);
}

/**
 * Takes a string and a int and prints it in curses sdtscr at the y value passed as line_num.
 * @param line The string to print
 * @param line_num The y value to print at in win
 * @param line_len The length of line to print
 * @param startX X coord of the win to start printing to.
 */
void s4c_print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length, int startX) {
    for (int i = 0; i < line_length; i++) {
        char c = line[i];
        int color_index = c - '0' + 8;
        if (color_index >= 0 && color_index < MAX_COLORS) {
            wattron(win, COLOR_PAIR(color_index));
            mvwaddch(win, curr_line_num, startX + 1 + i, ' ' | A_REVERSE);
            wattroff(win, COLOR_PAIR(color_index));
        }

    }
}

/**
 * Takes an empty 3D char array (frame, height, width) and a file to read the sprites from.
 * Checks if the file version is compatible with the current reader version, otherwise returns a negative error value.
 * Closes file pointer before returning.
 * File format should have a sprite line on each line.
 * Sets all the frames to the passed array.
 * @param sprites The char array to fill with all the frames.
 * @param f The file to read the sprites from.
 * @param frames The number of frames to load.
 * @param rows The number of rows in each sprite.
 * @param columns The number of columns in each sprite.
 * @see S4C_ERR_FILEVERSION
 * @see S4C_ERR_LOADSPRITES
 * @see S4C_FILEFORMAT_VERSION
 * @return A negative error value if loading fails or the number of sprites read.
 */
int s4c_load_sprites(char sprites[][MAXROWS][MAXCOLS], FILE* f, int frames, int rows, int columns) {

    if (frames == 0) {
	return 0;
    }

    char line[1024];
    char* file_version;
    char* token;
    const char* READER_VERSION = S4C_FILEFORMAT_VERSION;
    int row = 0, frame = -1;

    int check = -1;

    // Read the first line of the file to get the version number
    if (fgets(line, sizeof(line), f)) {
        // Parse the version number
        file_version = strtok(line, " \t\r\n");

	// Check if the file format has changed, abort and return the error
        if ((file_version == NULL) || ( (check = strcmp(file_version,READER_VERSION)) != 0) ) {
	    return S4C_ERR_FILEVERSION;
	};
    }


    while (fgets(line, sizeof(line), f)) {

	if (frame == frames) {
		break;
	}

        // Skip empty lines
        if (line[strspn(line, " \t\r\n")] == '\0') {
            continue;
        }

        // Skip comment lines
        if (line[strspn(line, " \t\r\n")] == '/') {
            continue;
        }

	// Skip heading line with the declaration
	if (frame == -1 && row == 0) {
		frame++;
		continue;
        }

        // Parse the line
        token = strtok(line, "\"");
        while (token != NULL) {
            if (token[0] != ',' && token[0] != '{' && token[0] != '}' && token[0] != '\t' && token[0] != '\n' && token[0] != '\"' && (token[0] != '}' && token[1] != ',' )) {
		strncpy(sprites[frame][row], token, columns);
		sprites[frame][row][columns] = '\0'; // add null-terminator to end of string
                row++;
                if (row == rows) {
                    frame++;
                    row = 0;
                }
            }
            token = strtok(NULL, "\"");
        }
    }

    //We close the file ourselves
    fclose(f);

    //Check if we have a strictly positive frame number or return the error
    if (!(frame > 0)) {
	return S4C_ERR_LOADSPRITES;
    }
    return frame;
}

/**
 * Calls s4c_animate_sprites_at_coords() with 0,0 as starting coordinates.
 * @see s4c_animate_sprites_at_coords()
 * @param sprites The sprites array.
 * @param w The window to print into.
 * @param repetition The number of times the animation will be cycled through.
 * @param frametime How many mseconds each frame is displayed.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @see S4C_ERR_CURSOR
 * @see S4C_ERR_SMALL_WIN
 * @return 1 if successful, a negative value for errors.
 */
int s4c_animate_sprites(char sprites[][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth) {
	return s4c_animate_sprites_at_coords(sprites, w,repetitions, frametime, num_frames, frameheight, framewidth, 0, 0);
}

/**
 * Takes a WINDOW pointer to print into and a string for the file passed.
 * Takes a pre-initialised array of sprites, valid format output by sprites.py or sheet_converter.py.
 * Color-character map is define in s4c_print_spriteline().
 * Sets all the frames to the passed array.
 * @see s4c_print_spriteline()
 * @param sprites The sprites array.
 * @param w The window to print into.
 * @param repetition The number of times the animation will be cycled through.
 * @param frametime How many mseconds each frame is displayed.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @see S4C_ERR_CURSOR
 * @see S4C_ERR_SMALL_WIN
 * @return 1 if successful, a negative value for errors.
 */
int s4c_animate_sprites_at_coords(char sprites[][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY) {
	int cursorCheck = curs_set(0); // We make the cursor invisible or return early with the error

	if (cursorCheck == ERR) {
		return S4C_ERR_CURSOR; //fprintf(stderr,"animate => Terminal does not support cursor visibility state.\n");
	}

	int rows = frameheight;
	int cols = framewidth;

	// Check if window is big enough
	int win_rows, win_cols;
	getmaxyx(w, win_rows, win_cols);
	if (win_rows < rows + startY || win_cols < cols + startX) {
		return S4C_ERR_SMALL_WIN; //fprintf(stderr, "animate => Window is too small to display the sprite.\n");
	}


	int current_rep = 0;
   	// Run the animation loop
   	while ( current_rep < repetitions ) {
		for (int i=0; i<num_frames+1;i++) {
			for (int j=0; j<rows; j++) {
				// Print current frame
				s4c_print_spriteline(w,sprites[i][j], j+startY+1, cols, startX);
				box(w,0,0);
				wrefresh(w);
			}
			wrefresh(w);
			// Refresh the screen
			napms(frametime);
			clear();
		};
		// We finished a whole cycle
		current_rep++;
	}
	// We make the cursor normal again
	curs_set(1);

	return 1;
}

/**
 * Takes a void pointer, to be cast to animate_args*, containing parameters to animate a sprite in a WINDOW, using a separate thread.
 * @see animate_args
 */
void *s4c_animate_sprites_thread_at(void *args_ptr) {

	animate_args* args = (animate_args *)args_ptr;
	WINDOW* w = args->win;
	int frametime = args->frametime;
	int num_frames = args->num_frames;
	int frameheight = args->frameheight;
	int framewidth = args->framewidth;
	int startX = args->startX;
	int startY = args->startY;

	int rows = frameheight;
	int cols = framewidth;

	// Check if window is big enough
	int win_rows, win_cols;
	getmaxyx(w, win_rows, win_cols);
	if (win_rows < rows + startY || win_cols < cols + startX) {
		fprintf(stderr, "[%s]  animate => Window is too small to display the sprite.\n",__func__);
		pthread_exit(NULL);
	}
	// Open the palette file and read the color values and names
	FILE* palette_file;
	palette_file = fopen("palette.gpl", "r");
	if (palette_file == NULL) {
	    fprintf(stderr, "[%s]  Error: could not open palette file.\n",__func__);
	    pthread_exit(NULL);
	}

	// Initialize all the colors and close palette file
	init_s4c_color_pairs(palette_file);

   	// Run the animation thread loop
   	do {
		for (int i=0; i<num_frames+1;i++) {
			box(w,0,0);
            		if (args->stop_thread == 1) {
                		break;
            		}
			for (int j=0; j<rows; j++) {
               			if (args->stop_thread == 1) {
                    			break;
                		}
				// Print current line for current frame
				s4c_print_spriteline(w,(args->sprites)[i][j], j+startY+1, cols, startX);
			}
			wrefresh(w);
			// Refresh the screen
			napms(frametime);
		};
	} while ( args->stop_thread != 1);

    pthread_exit(NULL);
    //FIXME
    //Is this a bug? Do we have to return NULL here?
    #ifdef _WIN32
    return NULL;
    #endif
}

/**
 * Takes a WINDOW pointer to print into.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Uses the passed sprites and displays a range of them in the passed window if it is big enough.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
 * @param sprites The sprites array.
 * @param w The window to print into.
 * @param repetition The number of times the animation will be cycled through.
 * @param frametime How many mseconds each frame is displayed.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @see S4C_ERR_SMALL_WIN
 * @return 1 if successful, a negative value for errors.
 */
int s4c_animate_rangeof_sprites_at_coords(char sprites[][MAXROWS][MAXCOLS], WINDOW* w, int fromFrame, int toFrame, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY) {
	//Validate requested range
	if (fromFrame < 0 || toFrame < 0 || fromFrame > toFrame || toFrame > num_frames ) {
		return S4C_ERR_RANGE;
	}

	int rows = frameheight;
	int cols = framewidth;

	// Check if window is big enough
	int win_rows, win_cols;
	getmaxyx(w, win_rows, win_cols);
	if (win_rows < rows + startY || win_cols < cols + startX) {
		return S4C_ERR_SMALL_WIN; //fprintf(stderr, "animate => Window is too small to display the sprite.\n");
	}


	int current_rep = 0;
   	// Run the animation loop
   	while ( current_rep < repetitions ) {
		//+1 to include toFrame index
		for (int i=fromFrame; i<toFrame+1 ;i++) {
			for (int j=0; j<rows; j++) {
				// Print current frame
				s4c_print_spriteline(w,sprites[i][j], j+startY+1, cols, startX);
				box(w,0,0);
				wrefresh(w);
			}
			wrefresh(w);
			// Refresh the screen
			napms(frametime);
			clear();
		};
		// We finished a whole cycle
		current_rep++;
	}
	return 1;
}

/**
 * Takes a WINDOW pointer to print into and an animation array, plus the index of requested frame to print.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
 * @param sprites The sprites array.
 * @param sprite_index The index of requested sprite.
 * @param w The window to print into.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @see S4C_ERR_SMALL_WIN
 * @return 1 if successful, a negative value for errors.
 */
int s4c_display_sprite_at_coords(char sprites[][MAXROWS][MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY) {
	//Validate requested range
	if (sprite_index < 0 || sprite_index > num_frames ) {
		return S4C_ERR_RANGE;
	}

	int rows = frameheight;
	int cols = framewidth;

	// Check if window is big enough
	int win_rows, win_cols;
	getmaxyx(w, win_rows, win_cols);
	if (win_rows < rows + startY || win_cols < cols + startX) {
		return S4C_ERR_SMALL_WIN; //fprintf(stderr, "animate => Window is too small to display the sprite.\n");
	}
	for (int j=0; j<rows; j++) {
		// Print current frame
		s4c_print_spriteline(w,sprites[sprite_index][j], j+startY+1, cols, startX);
	}
	box(w,0,0);
	wrefresh(w);
	return 1;
}

/**
 * Takes an S4C_Animation pointer as src and a WINDOW pointer to print into, plus the index of requested frame to print.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
 * @param src The S4C_Animation pointer used as source.
 * @param frame_index The index of requested frame.
 * @param w The window to print into.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @see S4C_ERR_SMALL_WIN
 * @return 1 if successful, a negative value for errors.
 */
int s4c_display_frame(S4C_Animation* src, int frame_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY) {

	char*** anim = *src;
	//Validate requested range
	if (frame_index < 0 || frame_index > num_frames ) {
		return S4C_ERR_RANGE;
	}

	int rows = frameheight;
	int cols = framewidth;

	// Check if window is big enough
	int win_rows, win_cols;
	getmaxyx(w, win_rows, win_cols);
	if (win_rows < rows + startY || win_cols < cols + startX) {
		return S4C_ERR_SMALL_WIN; //fprintf(stderr, "animate => Window is too small to display the sprite.\n");
	}
	for (int j=0; j<rows; j++) {
		// Print current frame
		s4c_print_spriteline(w,anim[frame_index][j], j+startY+1, cols, startX);
	}
	box(w,0,0);
	wrefresh(w);
	return 1;
}
#endif

/**
 * Takes a source animation vector matrix and a destination to copy to.
 * Takes ints to indicate how many frames, rows per frame and cols per row to copy.
 * @param frames How many frames to copy.
 * @param rows How many rows to copy.
 * @param cols How many cols to copy.
 * @param source The source sprites array.
 * @param dest The destination sprites array.
 */
void s4c_copy_animation(char source[][MAXROWS][MAXCOLS], char dest[MAXFRAMES][MAXROWS][MAXCOLS], int frames, int rows, int cols) {
  //Copy all frames
  for (int i = 0 ; i < frames+1; i++ ) {
    //Copy all rows for frame i
    for (int j = 0 ; j < rows+1; j++) {
      //Copy all columns for row j
     for (int k = 0 ; k < cols; k++) {
       //Assign current pixel, frame i row j col k
       dest[i][j][k] = source[i][j][k];
     }
    }
  }
}

/**
 * Takes a source animation vector matrix and a dinamyc array destination to copy to.
 * Takes ints to indicate how many frames, rows per frame and cols per row to copy.
 * Allocates the needed memory for the destination.
 * @param frames How many frames to copy.
 * @param rows How many rows to copy.
 * @param cols How many cols to copy.
 * @param source The source sprites array.
 * @param dest The destination sprites array.
 */
void s4c_copy_animation_alloc(S4C_Animation* dest, char source[][MAXROWS][MAXCOLS], int frames, int rows, int cols) {
    if (rows > MAXROWS) {
	fprintf(stderr,"{s4c} Error at [%s]: rows number was bigger than MAXROWS: [%i > %i]\n",__func__,rows,MAXROWS);
	exit(EXIT_FAILURE);
    }
    if (cols > MAXCOLS) {
	fprintf(stderr,"{s4c} Error at [%s]: cols number was bigger than MAXCOLS: [%i > %i]\n",__func__,cols,MAXCOLS);
	exit(EXIT_FAILURE);
    }
    *dest = malloc(frames * sizeof(char**));
    for (int i = 0; i < frames; i++) {
        (*dest)[i] = malloc(rows * sizeof(char*));
        for (int j = 0; j < rows; j++) {
            (*dest)[i][j] = malloc(cols * sizeof(char));
            for (int k = 0; k < cols; k++) {
                (*dest)[i][j][k] = source[i][j][k];
            }
        }
    }
}

/**
 * Takes an S4C_Animation pointer and frees it.
 * Takes ints to indicate how many frames, rows per frame to free.
 * @param animation The S4C_Animation pointer to free.
 * @param frames How many frames to free.
 * @param rows How many rows to free.
 */
void s4c_free_animation(S4C_Animation* animation, int frames, int rows) {
    if (animation == NULL || *animation == NULL) {
        return; // Nothing to free if the pointer or animation is NULL
    }

    char*** anim = *animation;

    for (int i = 0; i < frames; i++) {
        for (int j = 0; j < rows; j++) {
            free(anim[i][j]);
        }
        free(anim[i]);
    }

    free(anim);
    *animation = NULL; // Set the pointer to NULL after freeing the memory
}

#ifdef S4RAYLIB_BUILD
Color color_from_s4c_color(S4C_Color c) {
    return CLITERAL(Color){ c.red, c.green, c.blue, 255 };
}

void s4rl_print_spriteline(char* line, int coordY, int line_length, int startX, int pixelSize, Color color) {
    for (int i = 0; i < line_length; i++) {
        const char c = line[i];
        int color_index = c - '1';
        //Color converted = color_from_s4c_color(palette[color_index]);
        DrawRectangle(startX + (i * (pixelSize)), coordY, pixelSize, pixelSize, color);
    }
}

int s4rl_draw_sprite_at_coords(char sprite[][MAXCOLS], int frameheight, int framewidth, int startX, int startY, int pixelSize, Color color) {

	int rows = frameheight;
	int cols = framewidth;

	// TODO: Check if window is big enough
	//int win_rows, win_cols;
	//getmaxyx(w, win_rows, win_cols);
	//if (win_rows < rows + startY || win_cols < cols + startX) {
	//	return S4C_ERR_SMALL_WIN; //fprintf(stderr, "animate => Window is too small to display the sprite.\n");
	//}

    for (int j=0; j<rows; j++) {
        // Print current frame line
		s4rl_print_spriteline(sprite[j], (j*(pixelSize)) + (startY * pixelSize), cols, startX, pixelSize, color);
	}
	return 1;
}
#endif
