// jgabaut @ github.com/jgabaut
// SPDX-License-Identifier: GPL-3.0-only
/*
    Copyright (C) 2023-2024  jgabaut

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
#ifndef S4C_H
#define S4C_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define S4C_VERSION "0.5.0"
#define S4C_MAJOR_VERSION 0
#define S4C_MINOR_VERSION 5
#define S4C_PATCH_VERSION 0

/**
 * Defines current API version number from S4C_{MAJOR,MINOR,PATCH}.
 */
static const int S4C_API_VERSION_INT =
    (S4C_MAJOR_VERSION * 1000000 + S4C_MINOR_VERSION * 10000 + S4C_PATCH_VERSION * 100);
/**< Represents current version with numeric format.*/

/**
* Returns current s4c version as an integer.
*/
const int int_s4c_version(void);

/**
 * Returns current s4c version as a string.
 */
const char *string_s4c_version(void);

void s4c_printVersionToFile(FILE* f);
void s4c_echoVersionToFile(FILE* f);

#define S4C_PRINTVERSION() s4c_printVersionToFile(stdout); //Prints formatted version to stdout
#define S4C_ECHOVERSION() s4c_echoVersionToFile(stdout); //Prints version to stdout

void s4c_dbg_features(void);

#ifndef S4C_ANIMATE_H
#define S4C_ANIMATE_H
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#ifndef S4C_RAYLIB_EXTENSION
#ifndef _WIN32
#include <ncurses.h>
#else
#include <ncursesw/ncurses.h>
#endif // _WIN32
#include <pthread.h>
#endif // S4C_RAYLIB_EXTENSION


#define S4C_ANIMATE_VERSION "0.5.0"
#define S4C_ANIMATE_MAJOR_VERSION 0
#define S4C_ANIMATE_MINOR_VERSION 5
#define S4C_ANIMATE_PATCH_VERSION 0

/**
 * Defines current API version number from S4C_ANIMATE_{MAJOR,MINOR,PATCH}.
 */
static const int S4C_ANIMATE_API_VERSION_INT =
    (S4C_ANIMATE_MAJOR_VERSION * 1000000 + S4C_ANIMATE_MINOR_VERSION * 10000 + S4C_ANIMATE_PATCH_VERSION * 100);
/**< Represents current version with numeric format.*/

/**
 * Defines current version for s4c files.
 */
#define S4C_FILEFORMAT_VERSION "0.2.2"

void s4c_animate_printVersionToFile(FILE* f);
void s4c_animate_echoVersionToFile(FILE* f);

#define S4C_ANIMATE_PRINTVERSION() s4c_animate_printVersionToFile(stdout); //Prints formatted version to stdout
#define S4C_ANIMATE_ECHOVERSION() s4c_animate_echoVersionToFile(stdout); //Prints version to stdout

/**
 * Returns current s4c-animate version as an integer.
 */
const int int_s4c_animate_version(void);

/**
 * Returns current s4c-animate version as a string.
 */
const char *string_s4c_animate_version(void);

void s4c_animate_dbg_features(void);

#define S4C_MAX_COLORS 256
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

#ifndef S4C_MAX_LINE_LENGTH
#define S4C_MAX_LINE_LENGTH 1024
#endif // MAX_LINE_LENGTH

#ifndef S4C_MAXFRAMES
#define S4C_MAXFRAMES 121 /**< Defines the maximum number of sprites.*/
#endif // MAXFRAMES

#ifndef S4C_MAXROWS
#define S4C_MAXROWS 26 /**< Defines the maximum number of rows per sprite.*/
#endif // MAXROWS

#ifndef S4C_MAXCOLS
#define S4C_MAXCOLS 84 /**< Defines the maximum number of colums per sprite.*/
#endif //MAXCOLS

#define S4C_ERR_SMALL_WIN -1 /**< Defines the error value for a window too small for the animation.*/
#define S4C_ERR_FILEVERSION -2 /**< Defines the error value for a file version mismatch.*/
#define S4C_ERR_LOADSPRITES -3 /**< Defines the error value for a failure while loading sprites.*/
#define	S4C_ERR_TERMCOLOR -4 /**< Defines the error value for when the terminal doesn't support colors.*/
#define	S4C_ERR_TERMCHANGECOLOR -5 /**< Defines the error value for when the terminal doesn't support changing colors.*/
#define	S4C_ERR_CURSOR -6 /**< Defines the error value for when the terminal doesn't support changing cursor visibility.*/
#define	S4C_ERR_RANGE -7 /**< Defines the error value for invalid range requests for animate_rangeof_sprites_at_coords().*/

typedef struct S4C_Sprite {
    char data[S4C_MAXROWS][S4C_MAXCOLS];
    int frame_height;
    int frame_width;
    S4C_Color* palette;
    int palette_size;
} S4C_Sprite;

S4C_Sprite s4c_new_sprite(char data[][S4C_MAXCOLS], int frameheight, int framewidth, S4C_Color* palette, int palette_size);

#ifndef S4C_RAYLIB_EXTENSION
/*
 * Holds arguments for a call to animate_sprites_thread_at().
 * WIP.
 */
typedef struct animate_args {
    int stop_thread; /**< Stops the thread when false.*/
    WINDOW* win;/**< WINDOW to animate to.*/
    char sprites[S4C_MAXFRAMES][S4C_MAXROWS][S4C_MAXCOLS];/**< Array for the animation.*/
    int frametime;/**< How many ms a frame will stay on screen after drawing.*/
    int num_frames;/**< How many frames the animation has.*/
    int frameheight;/**< Height of the frames.*/
    int framewidth;/**< Width of the frames.*/
    int startX;/**< Starting X value to print at.*/
    int startY;/**< Starting Y value to print at.*/
} animate_args;

void init_s4c_color_pairs(FILE* palette_file);

void init_s4c_color_pair_ex(S4C_Color* color, int color_index, int bg_color_index);
void init_s4c_color_pair(S4C_Color* color, int color_index);
void init_s4c_color_pair_default_bg(S4C_Color* color, int color_index);

void test_s4c_color_pairs(WINDOW* win);

int s4c_check_term(void);
int s4c_check_win(WINDOW* win, int rows, int cols, int startX, int startY);

void slideshow_s4c_color_pairs(WINDOW* win);

void s4c_print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length, int startX);

int s4c_animate_sprites(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth);

void *s4c_animate_sprites_thread_at(void *animate_args);

int s4c_animate_sprites_at_coords(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY);

int s4c_animate_rangeof_sprites_at_coords(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], WINDOW* w, int fromFrame, int toFrame, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY);

int s4c_display_sprite_at_coords_checked(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);
int s4c_display_sprite_at_coords_unchecked(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);
int s4c_display_sprite_at_coords(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);

#ifdef S4C_EXPERIMENTAL
int s4c_display_frame(S4C_Animation* src, int frame_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY);
void s4c_copy_animation_alloc(S4C_Animation* dest, char source[][S4C_MAXROWS][S4C_MAXCOLS], int frames, int rows, int cols);
void s4c_free_animation(S4C_Animation* animation, int frames, int rows);
#endif
#endif

int s4c_load_sprites(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], FILE* file, int frames, int rows, int columns);
void s4c_copy_animation(char source[][S4C_MAXROWS][S4C_MAXCOLS], char dest[S4C_MAXFRAMES][S4C_MAXROWS][S4C_MAXCOLS], int frames, int rows, int cols);
#ifdef S4C_RAYLIB_EXTENSION
#ifndef RAYLIB_H
#include <raylib.h>
#endif

bool test_s4c_color_pairs(Rectangle* area, S4C_Color* palette);
Color color_from_s4c_color(S4C_Color c);
#define ColorFromS4CPalette(palette, idx) color_from_s4c_color((palette)[(idx) - S4C_BASE_COLOR_INDEX]) /**< Macro to retrieve a Color from S4C_Color palette by index.*/
//void s4rl_print_spriteline(char* line, int coordY, int line_length, int startX, int pixelSize, S4C_Color* palette, int palette_size);
void s4rl_draw_sprite_at_coords(char sprite[][S4C_MAXCOLS], int frameheight, int framewidth, int startX, int startY, int pixelSize, S4C_Color* palette, int palette_size);
int s4rl_draw_sprite_at_rect(char sprite[][S4C_MAXCOLS], Rectangle rect, int frameheight, int framewidth, int pixelSize, S4C_Color* palette, int palette_size);
#define DrawSprite(sprite, height, width, pixelsize, palette, palette_size) s4rl_draw_sprite_at_coords((sprite),(height),(width),0,0,(pixelsize),(palette),(palette_size))
#define DrawSpriteRect(sprite, rect, height, width, pixelsize, palette, palette_size) s4rl_draw_sprite_at_rect((sprite),(rect),(height),(width),(pixelsize),(palette),(palette_size))
int s4rl_draw_sprite_at_rect_V(char sprite[][S4C_MAXCOLS], Rectangle rect, Vector2 framesize, int pixelSize, S4C_Color* palette, int palette_size);
int s4rl_draw_s4c_sprite_at_rect(S4C_Sprite sprite, Rectangle rect, int pixelSize);
#define DrawS4CSpriteRect(sprite, rect, pixelsize) s4rl_draw_s4c_sprite_at_rect((sprite),(rect),(pixelsize))
#endif // S4C_RAYLIB_EXTENSION

#endif // S4C_ANIMATE_H

#ifdef S4C_HAS_GUI
#ifndef S4C_GUI_H_
#define S4C_GUI_H_
#include <stdlib.h>

/**
 * Function name to use in place of malloc.
 */
#ifndef S4C_GUI_MALLOC
#define S4C_GUI_MALLOC malloc
#endif // S4C_GUI_MALLOC

/**
 * Function name to use in place of calloc.
 */
#ifndef S4C_GUI_CALLOC
#define S4C_GUI_CALLOC calloc
#endif // S4C_GUI_CALLOC

#define S4C_GUI_MAJOR 0 /**< Represents current major release.*/
#define S4C_GUI_MINOR 0 /**< Represents current minor release.*/
#define S4C_GUI_PATCH 9 /**< Represents current patch release.*/

/* Defines current API version number from KLS_MAJOR, KLS_MINOR and KLS_PATCH.
 */
static const int S4C_GUI_API_VERSION_INT =
    (S4C_GUI_MAJOR * 1000000 + S4C_GUI_MINOR * 10000 + S4C_GUI_PATCH * 100);
/**< Represents current version with numeric format.*/

/**
 * Defines current API version string.
 */
static const char S4C_GUI_API_VERSION_STRING[] = "0.0.9"; /**< Represents current version with MAJOR.MINOR.PATCH format.*/

/**
 * Returns current s4c_gui version as a string.
 */
const char *string_s4c_gui_version(void);

/**
 * Returns current s4c_gui version as an integer.
 */
int int_s4c_gui_version(void);

typedef void*(s4c_gui_malloc_func)(size_t size); /**< Used to select an allocation function.*/
typedef void*(s4c_gui_calloc_func)(size_t count, size_t size); /**< Used to select a counted allocation function.*/
typedef void(s4c_gui_free_func)(void* obj); /**< Used to select a free function.*/

extern s4c_gui_malloc_func* s4c_gui_inner_malloc;
extern s4c_gui_calloc_func* s4c_gui_inner_calloc;

#ifndef TEXT_FIELD_H_
#define TEXT_FIELD_H_

#ifndef S4C_RAYLIB_EXTENSION
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif // _WIN32
#else
#include <raylib.h>
#endif // S4C_RAYLIB_EXTENSION

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct TextField_s *TextField;

typedef void(TextField_Full_Handler)(TextField);

typedef bool(TextField_Linter)(TextField, const void*);

#define TEXTFIELD_DEFAULT_LINTERS_TOT 1
extern TextField_Linter* default_linters[TEXTFIELD_DEFAULT_LINTERS_TOT+1];

extern const void* default_linter_args[TEXTFIELD_DEFAULT_LINTERS_TOT+1];

void warn_TextField(TextField txt);
bool lint_TextField_not_empty(TextField txt, const void* unused);
bool lint_TextField_equals_cstr(TextField txt, const void* cstr);
bool lint_TextField_whitelist(TextField txt, const void* whitelist);
bool lint_TextField_digits_only(TextField txt);
bool lint_TextField_chars_only(TextField txt);
#ifndef S4C_RAYLIB_EXTENSION
TextField new_TextField_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int start_x, int start_y, const char* prompt, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func);
TextField new_TextField_centered_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int bound_x, int bound_y, const char* prompt, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func);
#else
TextField new_TextField_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int start_x, int start_y, const char* prompt, Color box_color, Color txt_color, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func);
TextField new_TextField_centered_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int bound_x, int bound_y, const char* prompt, Color box_color, Color txt_color, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func);
#endif // S4C_RAYLIB_EXTENSION
bool lint_TextField(TextField txt_field);
TextField new_TextField(size_t max_size, int height, int width, int start_x, int start_y);
TextField new_TextField_centered(size_t max_size, int height, int width, int bound_x, int bound_y);
TextField new_TextField_linted(TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int start_x, int start_y);
TextField new_TextField_alloc(size_t max_size, int height, int width, int start_x, int start_y, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func);
void draw_TextField(TextField txt);
void clear_TextField(TextField txt);
#ifndef S4C_RAYLIB_EXTENSION
void use_clean_TextField(TextField txt_field);
#else
bool update_TextField(TextField txt_field);
#endif // S4C_RAYLIB_EXTENSION
void free_TextField(TextField txt_field);
const char* get_TextField_value(TextField txt_field);
int get_TextField_len(TextField txt_field);
#ifndef S4C_RAYLIB_EXTENSION
WINDOW* get_TextField_win(TextField txt_field);
#else
Rectangle get_TextField_rec(TextField txt_field);
#endif // S4C_RAYLIB_EXTENSION
#endif // TEXT_FIELD_H_

#ifndef TOGGLE_H_
#define TOGGLE_H_

#ifndef S4C_RAYLIB_EXTENSION
#ifdef _WIN32
#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#else
#include <ncurses.h>
#include <menu.h>
#endif // _WIN32
#else
#include <raylib.h>
#endif // S4C_RAYLIB_EXTENSION

#include <stdlib.h>

#ifndef TEXT_FIELD_H_
#error "This should not happen. TEXT_FIELD_H_ is defined in this same file."
#endif // TEXT_FIELD_H_

typedef enum {
    BOOL_TOGGLE,
    MULTI_STATE_TOGGLE,
    TEXTFIELD_TOGGLE,
} ToggleType;

typedef const char* (ToggleMultiState_Formatter)(int current_state);

typedef struct ToggleMultiState {
    int current_state;
    int num_states;
} ToggleMultiState;

typedef union ToggleState {
    bool bool_state; // For BOOL_TOGGLE
    ToggleMultiState ts_state; // For MULTI_STATE_TOGGLE
    TextField txt_state; // For TEXTFIELD_TOGGLE
} ToggleState;

typedef struct {
    ToggleType type;
    ToggleState state;
    char *label;
    bool locked; // Toggle lock
    ToggleMultiState_Formatter* multistate_formatter;
} Toggle;


struct ToggleMenu;

#ifndef S4C_RAYLIB_EXTENSION
typedef void(ToggleMenu_MouseEvent_Handler)(struct ToggleMenu, MEVENT* event);


// Reference: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/mouse.html
#ifndef TOGGLEMENU_DEFAULT_MOUSEEVENTS_MASK
#define TOGGLEMENU_DEFAULT_MOUSEEVENTS_MASK ALL_MOUSE_EVENTS
#endif // !TOGGLEMENU_DEFAULT_MOUSEEVENTS_MASK
#endif // S4C_RAYLIB_EXTENSION

typedef struct ToggleMenu_Conf {
    int height;
    int width;
    int start_x;
    int start_y;
    bool boxed;
    int quit_key;
    int statewin_width;
    int statewin_height;
    int statewin_start_x;
    int statewin_start_y;
    bool statewin_boxed;
    const char* statewin_label;
    int key_up;
    int key_right;
    int key_down;
    int key_left;
#ifndef S4C_RAYLIB_EXTENSION
    bool get_mouse_events;
    mmask_t mouse_events_mask;
    ToggleMenu_MouseEvent_Handler* mouse_handler;
#endif // S4C_RAYLIB_EXTENSION
} ToggleMenu_Conf;

typedef struct ToggleMenu {
    Toggle* toggles;
    int num_toggles;
    int height;
    int width;
    int start_x;
    int start_y;
    bool boxed;
    int quit_key;
    int statewin_width;
    int statewin_height;
    int statewin_start_x;
    int statewin_start_y;
    bool statewin_boxed;
    const char* statewin_label;
    int key_up;
    int key_right;
    int key_down;
    int key_left;
#ifndef S4C_RAYLIB_EXTENSION
    bool get_mouse_events;
    mmask_t mouse_events_mask;
    ToggleMenu_MouseEvent_Handler* mouse_handler;
#endif // S4C_RAYLIB_EXTENSION
} ToggleMenu;

#ifndef S4C_RAYLIB_EXTENSION
#define ToggleMenu_Fmt "ToggleMenu {\n  num_toggles: %i\n  height: %i\n  width: %i\n  start_x: %i\n  start_y: %i\n  boxed: %s\n  quit_key: %i\n  statewin_width: %i\n  statewin_height: %i\n  statewin_start_x: %i\n  statewin_start_y: %i\n  statewin_boxed: %s\n  statewin_label: %s\n  key_up: %i\n  key_right: %i\n  key_down: %i\n  key_left: %i\n  get_mouse_events: %s\n"

#define ToggleMenu_Arg(tm) (tm).num_toggles, (tm).height, (tm).width, (tm).start_x, (tm).start_y, ((tm).boxed ? "true" : "false"), (tm).quit_key, (tm).statewin_width, (tm).statewin_height, (tm).statewin_start_x, (tm).statewin_start_y, ((tm).statewin_boxed ? "true" : "false"), ((tm).statewin_label != NULL ? (tm).statewin_label : "null"), (tm).key_up, (tm).key_right, (tm).key_down, (tm).key_left, ((tm).get_mouse_events ? "true" : "false")
#else
#define ToggleMenu_Fmt "ToggleMenu {\n  num_toggles: %i\n  height: %i\n  width: %i\n  start_x: %i\n  start_y: %i\n  boxed: %s\n  quit_key: %i\n  statewin_width: %i\n  statewin_height: %i\n  statewin_start_x: %i\n  statewin_start_y: %i\n  statewin_boxed: %s\n  statewin_label: %s\n  key_up: %i\n  key_right: %i\n  key_down: %i\n  key_left: %i\n"

#define ToggleMenu_Arg(tm) (tm).num_toggles, (tm).height, (tm).width, (tm).start_x, (tm).start_y, ((tm).boxed ? "true" : "false"), (tm).quit_key, (tm).statewin_width, (tm).statewin_height, (tm).statewin_start_x, (tm).statewin_start_y, ((tm).statewin_boxed ? "true" : "false"), ((tm).statewin_label != NULL ? (tm).statewin_label : "null"), (tm).key_up, (tm).key_right, (tm).key_down, (tm).key_left)
#endif // S4C_RAYLIB_EXTENSION

#ifndef S4C_RAYLIB_EXTENSION
void default_ToggleMenu_mousehandler__(ToggleMenu toggle_menu, MEVENT* mouse_event);
#endif // S4C_RAYLIB_EXTENSION
ToggleMenu new_ToggleMenu_(Toggle* toggles, int num_toggles, ToggleMenu_Conf conf);
ToggleMenu new_ToggleMenu(Toggle* toggles, int num_toggles);
#ifndef S4C_RAYLIB_EXTENSION
ToggleMenu new_ToggleMenu_with_mouse_mask(Toggle* toggles, int num_toggles, ToggleMenu_MouseEvent_Handler* mouse_events_handler, mmask_t mouse_events_mask);
ToggleMenu new_ToggleMenu_with_mouse(Toggle* toggles, int num_toggles, ToggleMenu_MouseEvent_Handler* mouse_events_handler);
void draw_ToggleMenu_states(WINDOW *win, ToggleMenu toggle_menu);
void handle_ToggleMenu(ToggleMenu toggle_menu);
#else
void draw_ToggleMenu_states(Rectangle area, ToggleMenu toggle_menu);
void update_ToggleMenu(ToggleMenu toggle_menu);
void draw_ToggleMenu(ToggleMenu toggle_menu);
#endif // S4C_RAYLIB_EXTENSION
void free_ToggleMenu(ToggleMenu toggle_menu);
#endif // TOGGLE_H_

#endif // S4C_GUI_H_
#endif // S4C_HAS_GUI

#endif // S4C_H
