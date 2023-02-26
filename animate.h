#include <ncurses.h>
//These define the colors for init_pair() without an order
#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define WHITE 8

#define MAXFRAMES 121 /**< Defines the maximum number of sprites.*/
#define MAXROWS 26 /**< Defines the maximum number of rows per sprite.*/
#define MAXCOLS 84 /**< Defines the maximum number of colums per sprite.*/

static void print_spriteline(WINDOW* w, char* line, int line_num);
static char *trim(char *str);
void load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], FILE* file, int rows, int columns);
void init_s4c_color_pairs();
void animate_file(WINDOW* w, FILE* file, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);
