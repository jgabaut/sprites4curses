#include <ncurses.h>
//These define the colors for init_pair() without an order
#define RED 1
#define YELLOW 2
#define GREEN 3
#define CYAN 4
#define BLUE 5
#define MAGENTA 6
#define BLACK 7
#define WHITE 8

#define NUM_FRAMES 31 /**< Defines the number of sprites, +1.*/
#define ROWS 18 /**< Defines the number of rows per sprite, +1.*/
#define COLS 18 /**< Defines the number of colums per sprite, +1.*/

#define FRAMETIME 67 /**< Defines for how many millisecs a sprite should stay on screen.*/

static void print_spriteline(WINDOW* w, char* line, int line_num);
static char *trim(char *str);
void load_sprites(char sprites[NUM_FRAMES][ROWS][COLS], const char *filename);
static void animate_usage(char* progname);
void init_color_pairs();
void animate_file(WINDOW* w, char* filename);
void demo(int argc, char** argv); 
