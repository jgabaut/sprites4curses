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

#ifndef S4C_ANIMATE_H
#define S4C_ANIMATE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#ifndef S4C_RAYLIB_EXTENSION
#ifndef _WIN32
#include <ncurses.h>
#else
#include <ncursesw/ncurses.h>
#endif
#include <pthread.h>
#endif


#define S4C_ANIMATE_VERSION "0.4.0"
#define S4C_ANIMATE_MAJOR_VERSION 0
#define S4C_ANIMATE_MINOR_VERSION 4
#define S4C_ANIMATE_PATCH_VERSION 0

/**
 * Defines current version for s4c files.
 */
#define S4C_FILEFORMAT_VERSION "0.2.2"

void s4c_printVersionToFile(FILE* f);
void s4c_echoVersionToFile(FILE* f);

#define S4C_PRINTVERSION() s4c_printVersionToFile(stdout); //Prints formatted version to stdout
#define S4C_ECHOVERSION() s4c_echoVersionToFile(stdout); //Prints version to stdout


#define MAX_COLORS 256
#define S4C_PALETTEFILE_MAX_COLOR_NAME_LEN 256 /**< Defines max size for the name strings in palette.gpl.*/

#ifdef S4C_EXPERIMENTAL
typedef char*** S4C_Animation;
#endif

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
void debug_s4c_color(S4C_Color* color);

/*
 * Defines the lowest index that will be used by s4c. A value <=8 is not recommended, as when initialising colorpairs we'd be reloading default ones.
 * WIP.
 * @see init_s4c_color_pairs();
 * @see S4C_Color_Index
 */
#define	S4C_BASE_COLOR_INDEX 9
/*
 * Defines integer constants to index s4c' color pairs, as expected from the initialised color_pairs.
 * WIP.
 * @see init_s4c_color_pairs();
 */
typedef enum S4C_Color_Index {
	S4C_BLACK=S4C_BASE_COLOR_INDEX,
	S4C_RED,
	S4C_BRIGHT_GREEN,
	S4C_BRIGHT_YELLOW,
	S4C_BLUE,
	S4C_MAGENTA,
	S4C_CYAN,
	S4C_WHITE,
	S4C_ORANGE,
	S4C_LIGHT_BROWN,
	S4C_DARK_BROWN,
	S4C_PURPLE,
	S4C_DARK_GREEN,
	S4C_GREY,
	S4C_LIGHT_YELLOW,
	S4C_LIGHT_BLUE,
	S4C_DARK_YELLOW,
	S4C_DARK_OLIVE,
	S4C_LIGHT_OLIVE,
	S4C_OLIVE,
	S4C_DARK_CHERRY,
	S4C_LIGHT_CHERRY,
	S4C_CHERRY,
	S4C_SALMON,
	S4C_DARK_BLUE,
	S4C_VIOLET,
	S4C_INDIGO,
	S4C_LIGHT_ORANGE,
	S4C_TEAL,
	S4C_DARK_CYAN,
	S4C_DARK_PURPLE,
	S4C_LIGHT_PURPLE
} S4C_Color_Index;

#define	S4C_MIN_COLOR_INDEX S4C_BLACK
#define S4C_MAX_COLOR_INDEX S4C_LIGHT_PURPLE
#define S4C_MAX_COLOR_NAME_LEN 17

const char* s4c_color_name(S4C_Color_Index color_index);

/**
 * Holds string names for each S4C_Color_Index value.
 */
extern const char* s4c_color_strings[S4C_MAX_COLOR_INDEX+1];

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

typedef struct S4C_Sprite {
    char data[MAXROWS][MAXCOLS];
    int frame_height;
    int frame_width;
    S4C_Color* palette;
    int palette_size;
} S4C_Sprite;

S4C_Sprite s4c_new_sprite(char data[][MAXCOLS], int frameheight, int framewidth, S4C_Color* palette, int palette_size);

#ifndef S4C_RAYLIB_EXTENSION
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

void test_s4c_color_pairs(WINDOW* win);

void slideshow_s4c_color_pairs(WINDOW* win);

void s4c_print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length, int startX);

int s4c_animate_sprites(char sprites[][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);

void *s4c_animate_sprites_thread_at(void *animate_args);

int s4c_animate_sprites_at_coords(char sprites[][MAXROWS][MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY);

int s4c_animate_rangeof_sprites_at_coords(char sprites[][MAXROWS][MAXCOLS], WINDOW* w, int fromFrame, int toFrame, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY);

int s4c_display_sprite_at_coords(char sprites[][MAXROWS][MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);
#ifdef S4C_EXPERIMENTAL
int s4c_display_frame(S4C_Animation* src, int frame_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);
void s4c_copy_animation_alloc(S4C_Animation* dest, char source[][MAXROWS][MAXCOLS], int frames, int rows, int cols);
void s4c_free_animation(S4C_Animation* animation, int frames, int rows);
#endif
#endif

int s4c_load_sprites(char sprites[][MAXROWS][MAXCOLS], FILE* file, int frames, int rows, int columns);
void s4c_copy_animation(char source[][MAXROWS][MAXCOLS], char dest[MAXFRAMES][MAXROWS][MAXCOLS], int frames, int rows, int cols);
#ifdef S4C_RAYLIB_EXTENSION
#ifndef RAYLIB_H
#include <raylib.h>
#endif

Color color_from_s4c_color(S4C_Color c);
//void s4rl_print_spriteline(char* line, int coordY, int line_length, int startX, int pixelSize, S4C_Color* palette, int palette_size);
void s4rl_draw_sprite_at_coords(char sprite[][MAXCOLS], int frameheight, int framewidth, int startX, int startY, int pixelSize, S4C_Color* palette, int palette_size);
int s4rl_draw_sprite_at_rect(char sprite[][MAXCOLS], Rectangle rect, int frameheight, int framewidth, int pixelSize, S4C_Color* palette, int palette_size);
int s4rl_draw_sprite_at_rect_V(char sprite[][MAXCOLS], Rectangle rect, Vector2 framesize, int pixelSize, S4C_Color* palette, int palette_size);
int s4rl_draw_s4c_sprite_at_rect(S4C_Sprite sprite, Rectangle rect, int pixelSize);
#endif // S4C_RAYLIB_EXTENSION

#endif
