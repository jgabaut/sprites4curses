#ifndef S4C_ANIMATE_H
#define S4C_ANIMATE_H

#include <ncurses.h>

#define MAX_COLORS 256
#define MAX_COLOR_NAME_LEN 256 /**< Defines max size for the name strings in palette.gpl.*/

// These define constants for the colors prepared by init_s4c_color_pairs().
#define S4C_BLACK 1
#define S4C_RED 2
#define S4C_BRIGHT_GREEN 3
#define S4C_BRIGHT_YELLOW 4
#define S4C_BLUE 5
#define S4C_MAGENTA 6
#define S4C_CYAN 7
#define S4C_WHITE 8
#define S4C_ORANGE 9
#define S4C_LIGHT_BROWN 10
#define S4C_DARK_BROWN 11
#define S4C_PURPLE 12
#define S4C_DARK_GREEN 13
#define S4C_LIGHT_YELLOW 14
#define S4C_LIGHT_BLUE 15

#define MAX_LINE_LENGTH 1024

#define MAXFRAMES 121 /**< Defines the maximum number of sprites.*/
#define MAXROWS 26 /**< Defines the maximum number of rows per sprite.*/
#define MAXCOLS 84 /**< Defines the maximum number of colums per sprite.*/
		
#define S4C_ERR_SMALL_WIN -1 /**< Defines the error value for a window too small for the animation.*/
#define S4C_ERR_FILEVERSION -2 /**< Defines the error value for a file version mismatch.*/
#define S4C_ERR_LOADSPRITES -3 /**< Defines the error value for a failure while loading sprites.*/

void init_s4c_color_pairs(FILE* palette_file);
static void print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length);
static char *trim(char *str);
int load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], FILE* file, int rows, int columns);
int animate_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);

#endif
