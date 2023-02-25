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

#define MAXFRAMES 61 /**< Defines the maximum number of sprites.*/
#define DEMOFRAMES 30 /**< Defines the number of sprites in the demo.*/
#define MAXROWS 26 /**< Defines the maximum number of rows per sprite.*/
#define MAXCOLS 84 /**< Defines the maximum number of colums per sprite.*/
#define DEMOROWS 18 /**< Defines the maximum number of rows per sprite.*/
#define DEMOCOLS 18 /**< Defines the maximum number of colums per sprite.*/

#define DEMOFRAMETIME 67 /**< Defines for how many millisecs a sprite should stay on screen in the demo.*/

static void print_spriteline(WINDOW* w, char* line, int line_num);
static char *trim(char *str);
void load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], const char *filename, int rows, int columns);
void animate_demo_usage(char* progname);
void init_color_pairs();
void animate_file(WINDOW* w, char* filename, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);
void demo(); 
