#ifndef S4C_ANIMATE_H
#define S4C_ANIMATE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>

#define S4C_ANIMATE_VERSION "0.2.12"
#define S4C_ANIMATE_MAJOR_VERSION 0
#define S4C_ANIMATE_MINOR_VERSION 2
#define S4C_ANIMATE_PATCH_VERSION 12

void s4c_printVersionToFile(FILE* f);
void s4c_echoVersionToFile(FILE* f);

#define S4C_PRINTVERSION() s4c_printVersionToFile(stdout); //Prints formatted version to stdout
#define S4C_ECHOVERSION() s4c_echoVersionToFile(stdout); //Prints version to stdout


#define MAX_COLORS 256
#define MAX_COLOR_NAME_LEN 256 /**< Defines max size for the name strings in palette.gpl.*/

/*
 * Defines a color.
 * WIP.
 */
typedef struct S4C_Color {
    int red; /**< Red component.*/
    int green; /**< Green component.*/
    int blue; /**< Blue component.*/
    char name[50]; /**< Name for the color.*/
} S4C_Color;

void debug_s4c_color_2file(S4C_Color* color, FILE* fp);

// These define constants for the colors prepared by init_s4c_color_pairs().
#define S4C_BLACK 9
#define S4C_MIN_COLOR_INDEX S4C_BLACK
#define S4C_RED 10
#define S4C_BRIGHT_GREEN 11
#define S4C_BRIGHT_YELLOW 12
#define S4C_BLUE 13
#define S4C_MAGENTA 14
#define S4C_CYAN 15
#define S4C_WHITE 16
#define S4C_ORANGE 17
#define S4C_LIGHT_BROWN 18
#define S4C_DARK_BROWN 19
#define S4C_PURPLE 20
#define S4C_DARK_GREEN 21
#define S4C_LIGHT_YELLOW 22
#define S4C_LIGHT_BLUE 23
#define S4C_MAX_COLOR_INDEX S4C_LIGHT_BLUE

#define MAX_LINE_LENGTH 1024

#define MAXFRAMES 121 /**< Defines the maximum number of sprites.*/
#define MAXROWS 26 /**< Defines the maximum number of rows per sprite.*/
#define MAXCOLS 84 /**< Defines the maximum number of colums per sprite.*/

#define S4C_ERR_SMALL_WIN -1 /**< Defines the error value for a window too small for the animation.*/
#define S4C_ERR_FILEVERSION -2 /**< Defines the error value for a file version mismatch.*/
#define S4C_ERR_LOADSPRITES -3 /**< Defines the error value for a failure while loading sprites.*/
#define	S4C_ERR_TERMCOLOR -4 /**< Defines the error value for when the terminal doesn't support colors.*/
#define	S4C_ERR_TERMCHANGECOLOR -5 /**< Defines the error value for when the terminal doesn't support changing colors.*/
#define	S4C_ERR_CURSOR -6 /**< Defines the error value for when the terminal doesn't support changing cursor visibility.*/
#define	S4C_ERR_RANGE -7 /**< Defines the error value for invalid range requests for animate_rangeof_sprites_at_coords().*/

/*
 * Holds arguments for a call to animate_sprites_thread_at().
 * WIP.
 */
typedef struct animate_args {
    int stop_thread; /**< Stops the thread when false.*/
    WINDOW* win;/**< WINDOW to animate to.*/
    char sprites[MAXFRAMES][MAXROWS][MAXCOLS];/**< Array for the animation.*/
    int frametime;/**< How many ms a frame will stay on screen after drawing.*/
    int num_frames;/**< How many frames the animation has.*/
    int frameheight;/**< Height of the frames.*/
    int framewidth;/**< Width of the frames.*/
    int startX;/**< Starting X value to print at.*/
    int startY;/**< Starting Y value to print at.*/
} animate_args;

void init_s4c_color_pairs(FILE* palette_file);

void init_s4c_color_pair(S4C_Color* color, int color_index);

void test_s4c_color_pairs(WINDOW* win, FILE* palette_file);

void print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length, int startX);

int load_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], FILE* file, int rows, int columns);

int animate_sprites(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);

void *animate_sprites_thread_at(void *animate_args);

int animate_sprites_at_coords(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY);

int animate_rangeof_sprites_at_coords(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], WINDOW* w, int fromFrame, int toFrame, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY);

int display_sprite_at_coords(char sprites[MAXFRAMES][MAXROWS][MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);

void copy_animation(char source[MAXFRAMES][MAXROWS][MAXCOLS], char dest[MAXFRAMES][MAXROWS][MAXCOLS], int frames, int rows, int cols);
#endif
