#ifndef S4C_ANIMATE_H
#define S4C_ANIMATE_H

#include <ncurses.h>

#define MAX_COLORS 256
#define MAX_COLOR_NAME_LEN 256

typedef struct {
    short fg;
    short bg;
    char name[MAX_COLOR_NAME_LEN];
} color_pair_t;

//These define the colors for init_pair() without an order
#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define WHITE 8

#define MAX_LINE_LENGTH 1024

#define MAXFRAMES 121 /**< Defines the maximum number of sprites.*/
#define MAXROWS 26 /**< Defines the maximum number of rows per sprite.*/
#define MAXCOLS 84 /**< Defines the maximum number of colums per sprite.*/
		
#define S4C_ERR_SMALL_WIN -1 /**< Defines the error value for a window too small for the animation.*/
#define S4C_ERR_FILEVERSION -2 /**< Defines the error value for a file version mismatch.*/
#define S4C_ERR_LOADSPRITES -3 /**< Defines the error value for a failure while loading sprites.*/

void init_s4c_color_pairs();
static void init_color_pairs_from_palette();
static void print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length);
static char *trim(char *str);
int load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], FILE* file, int rows, int columns);
int animate_file(WINDOW* w, FILE* file, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);

#endif
