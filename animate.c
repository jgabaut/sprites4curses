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
void print_spriteline(char* line, int line_num) {
	int color = -1;

	for (int i=0; i<18; i++) {
		char c = line[i];
		switch (c) {
			case '\n': {
				return;
				   }
			case 'c': {
				color = CYAN;
				  }
			break;
			case 'b': {
				color = BLUE;
				  }
			break;
			case 'r': {
				color = RED;
				  }
			break;
			case 'k': {
				color = BLACK;
				  }
			break;
			case 'w': {
				color = WHITE;
				  }
			break;
			case 'm': {
				color = MAGENTA;
				  }
			break;
			case 'g': {
				color = GREEN;
				  }
			break;
			case 'y': {
				color = YELLOW;
				  }
			break;
				

		}
		attron(COLOR_PAIR(color));
        	mvaddch(line_num, 2+i, ' '|A_REVERSE);
		attroff(COLOR_PAIR(color));
	}
};

/* 
 * Takes a string and trims whitespace at the edges.
 * @param str The string to trim.
 * @return str The trimmed string.
 */
char *trim(char *str) {
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
 * Takes an empty 3D char array (frame, height, width) and a filename to read the sprites from.
 * File format should have a sprite line on each line.
 * Sets all the frames to the passed array.
 * @param sprites The char array to fill with all the frames.
 * @param filename The file to read the sprites from.
 */
void load_sprites(char sprites[NUM_FRAMES][ROWS][COLS], const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        fprintf(stderr,"Error opening file %s\n",filename);
        exit(EXIT_FAILURE);
    }

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
            if (token[0] != ',' && token[0] != '{' && token[0] != '}' && token[0] != '\t' && token[0] != '\n' && (token[0] != '}' && token[1] != ',')) {
                strcpy(sprites[frame-1][row], token);
                row++;
                if (row == ROWS-1) {
                    frame++;
                    row = 0;
                }
            }
            token = strtok(NULL, "\"");
        }
    }

    fclose(f);
}

void usage(char* progname) {
    fprintf(stderr,"Usage: %s <animation_file.txt>\n",progname);
    exit(EXIT_FAILURE);
}

/*
 * Takes an integer for number of arguments and a string array with the first string being the file name containing the sprites.
 * Puts on a demo of the contained animation file.
 * File format should have a sprite line on each line, or be a valid array definition.
 * Color-character map is define in print_spriteline().
 * Sets all the frames to the passed array.
 * @see print_spriteline()
 * @param sprites The char array to fill with all the frames.
 * @param filename The file to read the sprites from.
 */
int demo(int argc, char** argv)
{
	if (argc != 2) {
		usage(argv[0]);
	}
	// Initialize ncurses
	initscr();
	start_color();
	cbreak();
	noecho();

	// Initialize all the colors
	init_pair(RED, COLOR_RED, COLOR_BLACK);
	init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
	init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);

    	// Prepare the frames
	char sprites[NUM_FRAMES][ROWS][COLS]; 
	load_sprites(sprites, argv[1]);

	clear();

   	// Run the animation loop
   	while (1) {
		for (int i=0; i<NUM_FRAMES;i++) {
			for (int j=0; j<18; j++) {
				// Print current frame
				print_spriteline(sprites[i][j], j);
			}
			//mvprintw(22,2, "Frame %i", i); //print current frame num
			// Refresh the screen
			refresh();
			napms(FRAMETIME);
			move(0,0);
			clear();
		};      	
    }

    // Clean up ncurses
    endwin();
    return 0;
}
