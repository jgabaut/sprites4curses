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
        char name[MAX_COLOR_NAME_LEN];
        if (sscanf(line, "%d %d %d %[^\n]", &r, &g, &b, name) != 4) {
            fprintf(stderr, "Error: could not parse palette line: %s\n", line);
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
 * Demoes all colors supported by the passed palette file in the passed WINDOW. Not guaranteed to work.
 * Since it uses indexes defined by default from animate.h, it should work only when your passed palette file has color pairs for the expected index range.
 * @param win The window to print the demo to.
 * @param palette_file The palette file used to initialise s4c.
 */
void test_s4c_color_pairs(WINDOW* win, FILE* palette_file) {
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
 * Takes a string and a int and prints it in curses sdtscr at the y value passed as line_num.
 * @param line The string to print
 * @param line_num The y value to print at in win
 * @param line_len The length of line to print
 * @param startX X coord of the win to start printing to.
 */
void print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length, int startX) {
    for (int i = 0; i < line_length; i++) {
        char c = line[i];
        int color_index = c - 'a' + 8;
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
 * @param rows The number of rows in each sprite.
 * @param columns The number of columns in each sprite.
 * @see S4C_ERR_FILEVERSION
 * @see S4C_ERR_LOADSPRITES
 * @return A negative error value if loading fails or the number of sprites read.
 */
int load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], FILE* f, int rows, int columns) {

    char line[1024];
    char* file_version;
    char* token;
    char* READER_VERSION = "0.1.5";
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
 * Calls animate_sprites_at_coords() with 0,0 as starting coordinates.
 * @see animate_sprites_at_coords()
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
int animate_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth) {
	return animate_sprites_at_coords(sprites, w,repetitions, frametime, num_frames, frameheight, framewidth, 0, 0);
}

/**
 * Takes a WINDOW pointer to print into and a string for the file passed.
 * Takes a pre-initialised array of sprites, valid format output by sprites.py or sheet_converter.py.
 * Color-character map is define in print_spriteline().
 * Sets all the frames to the passed array.
 * @see print_spriteline()
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
int animate_sprites_at_coords(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY) {
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
				print_spriteline(w,sprites[i][j], j+startY+1, cols, startX);
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
void *animate_sprites_thread_at(void *args_ptr) {

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
		fprintf(stderr, "animate => Window is too small to display the sprite.\n");
		pthread_exit(NULL);
	}
	// Open the palette file and read the color values and names
	FILE* palette_file;
	palette_file = fopen("palette.gpl", "r");
	if (palette_file == NULL) {
	    fprintf(stderr, "Error: could not open palette file.\n");
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
				print_spriteline(w,(args->sprites)[i][j], j+startY+1, cols, startX);
			}
			wrefresh(w);
			// Refresh the screen
			napms(frametime);
		};
	} while ( args->stop_thread != 1);

    pthread_exit(NULL);
}

/**
 * Takes a WINDOW pointer to print into.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Uses the passed sprites and displays a range of them in the passed window if it is big enough.
 * Color-character map is define in print_spriteline().
 * @see print_spriteline()
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
int animate_rangeof_sprites_at_coords(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int fromFrame, int toFrame, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY) {
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
				print_spriteline(w,sprites[i][j], j+startY+1, cols, startX);
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
 * Color-character map is define in print_spriteline().
 * Sets all the frames to the passed array.
 * @see print_spriteline()
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
int display_sprite_at_coords(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY) {
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
		print_spriteline(w,sprites[sprite_index][j], j+startY+1, cols, startX);
	}
	box(w,0,0);
	wrefresh(w);
	return 1;
}

/**
 * Takes a source animation vector matrix and a destination to copy to.
 * Takes ints to indicate how many frames, rows per frame and cols per row to copy.
 * @param frames How many frames to copy.
 * @param rows How many rows to copy.
 * @param cols How many cols to copy.
 * @param source The source sprites array.
 * @param dest The destination sprites array.
 */
void copy_animation(char source[MAXFRAMES][MAXROWS][MAXCOLS], char dest[MAXFRAMES][MAXROWS][MAXCOLS], int frames, int rows, int cols) {
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
