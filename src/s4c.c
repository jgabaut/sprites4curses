// jgabaut @ github.com/jgabaut
// SPDX-License-Identifier: GPL-3.0-only
/*
    Copyright (C) 2023-2025  jgabaut

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
#include "s4c.h"

/**
 * Returns the constant int representing current version for s4c.
 * @return A constant int in numeric format for current s4c version.
 */
const int int_s4c_version(void)
{
    return S4C_API_VERSION_INT;
}

/**
 * Returns the constant string representing current version for s4c.
 * @return A constant char pointer for current s4c version.
 */
const char *string_s4c_version(void)
{
    return S4C_VERSION;
}

/**
 * Prints formatted s4c version.
 */
void s4c_printVersionToFile(FILE* f)
{
    if (!f) {
        fprintf(stderr,"Error while trying to print formatted s4c version, invalid file pointer.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(f,"sprites4curses/animate.h v%s\n",S4C_VERSION);
}

/**
 * Prints s4c version.
 */
void s4c_echoVersionToFile(FILE* f)
{
    if (!f) {
        fprintf(stderr,"Error while trying to print s4c version, invalid file pointer.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(f,"%s\n",S4C_VERSION);
}

/**
 * Prints enabled s4c features to stderr.
 */
void s4c_dbg_features(void)
{
#ifdef S4C_HAS_ANIMATE
    bool s4c_has_animate = true;
#else
    bool s4c_has_animate = false;
#endif
#ifdef S4C_HAS_GUI
    bool s4c_has_gui = true;
#else
    bool s4c_has_gui = false;
#endif
#ifdef S4C_RAYLIB_EXTENSION
    bool s4c_raylib_extension = true;
    bool s4c_ncurses_extension = false;
#else
    bool s4c_raylib_extension = false;
    bool s4c_ncurses_extension = true;
#endif
#ifdef S4C_RL_QUIETER
    bool s4c_raylib_quieter = true;
#else
    bool s4c_raylib_quieter = false;
#endif
#ifdef S4C_UNCHECKED
    bool s4c_ncurses_unchecked = true;
#else
    bool s4c_ncurses_unchecked = false;
#endif
#ifdef S4C_EXPERIMENTAL
    bool s4c_experimental = true;
#else
    bool s4c_experimental = false;
#endif
    bool features[7] = {
        [0] = s4c_has_animate,
        [1] = s4c_has_gui,
        [2] = s4c_ncurses_extension,
        [3] = s4c_ncurses_unchecked,
        [4] = s4c_raylib_extension,
        [5] = s4c_raylib_quieter,
        [6] = s4c_experimental,
    };
    int total_enabled = 0;
    for (int i=0; i<7; i++) {
        if (features[i]) {
            total_enabled += 1;
        }
    }
    fprintf(stderr, "[S4C]    Enabled features: {");
    if (total_enabled == 0) {
        fprintf(stderr, "none}\n");
        return;
    } else {
        if (s4c_has_animate) {
            fprintf(stderr, "animate%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_has_gui) {
            fprintf(stderr, "gui%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_raylib_extension) {
            fprintf(stderr, "animate-raylib%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_ncurses_extension) {
            fprintf(stderr, "animate-ncurses%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_raylib_quieter) {
            fprintf(stderr, "animate-quieter%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_ncurses_unchecked) {
            fprintf(stderr, "animate-unchecked%s", (total_enabled > 1 ? ", " : ""));
        }
        if (s4c_experimental) {
            fprintf(stderr, "animate-exper");
        }
        fprintf(stderr, "}\n");
    }
}

#ifdef S4C_ANIMATE_H
/**
 * Prints formatted animate version.
 */
void s4c_animate_printVersionToFile(FILE* f)
{
    if (!f) {
        fprintf(stderr,"Error while trying to print formatted s4c-animate version, invalid file pointer.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(f,"sprites4curses/animate.h v%s\n",S4C_ANIMATE_VERSION);
}

/**
 * Prints animate version.
 */
void s4c_animate_echoVersionToFile(FILE* f)
{
    if (!f) {
        fprintf(stderr,"Error while trying to print s4c-animate version, invalid file pointer.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(f,"%s\n",S4C_ANIMATE_VERSION);
}

/**
 * Returns the constant int representing current version for s4c-animate.
 * @return A constant int in numeric format for current s4c-animate version.
 */
const int int_s4c_animate_version(void)
{
    return S4C_ANIMATE_API_VERSION_INT;
}

/**
 * Returns the constant string representing current version for s4c-animate.
 * @return A constant char pointer for current s4c-animate version.
 */
const char *string_s4c_animate_version(void)
{
    return S4C_ANIMATE_VERSION;
}

/**
 * Prints enabled s4c-animate features to stderr.
 */
void s4c_animate_dbg_features(void)
{
#ifdef S4C_RAYLIB_EXTENSION
    bool s4c_raylib_extension = true;
    bool s4c_ncurses_extension = false;
#else
    bool s4c_raylib_extension = false;
    bool s4c_ncurses_extension = true;
#endif
#ifdef S4C_RL_QUIETER
    bool s4c_raylib_quieter = true;
#else
    bool s4c_raylib_quieter = false;
#endif
#ifdef S4C_UNCHECKED
    bool s4c_ncurses_unchecked = true;
#else
    bool s4c_ncurses_unchecked = false;
#endif
#ifdef S4C_EXPERIMENTAL
    bool s4c_experimental = true;
#else
    bool s4c_experimental = false;
#endif
    bool features[5] = {
        [0] = s4c_ncurses_extension,
        [1] = s4c_ncurses_unchecked,
        [2] = s4c_raylib_extension,
        [3] = s4c_raylib_quieter,
        [4] = s4c_experimental,
    };
    int total_enabled = 0;
    for (int i=0; i<5; i++) {
        if (features[i]) {
            total_enabled += 1;
        }
    }
    fprintf(stderr, "[S4C]    Enabled features: {");
    if (total_enabled == 0) {
        fprintf(stderr, "none}\n");
        return;
    } else {
        if (s4c_raylib_extension) {
            fprintf(stderr, "animate-raylib%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_ncurses_extension) {
            fprintf(stderr, "animate-ncurses%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_raylib_quieter) {
            fprintf(stderr, "animate-quieter%s", (total_enabled > 1 ? ", " : ""));
            total_enabled -= 1;
        }
        if (s4c_ncurses_unchecked) {
            fprintf(stderr, "animate-unchecked%s", (total_enabled > 1 ? ", " : ""));
        }
        if (s4c_experimental) {
            fprintf(stderr, "animate-exper");
        }
        fprintf(stderr, "}\n");
    }
}

/**
 * Takes a S4C_Color pointer and a FILE pointer to print to.
 *
 * @param color The color to debug.
 * @param fp The file to debug to.
 */
void debug_s4c_color_2file(S4C_Color* color, FILE* fp)
{
    if (!fp) {
        fprintf(stderr,"Error while trying to debug an S4C_Color, invalid file pointer.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp,"[S4C_Color] => { red: [%i], green: [%i], blue: [%i], name: [%s] }\n", color->red, color->green, color->blue, color->name);
}

/**
 * Takes a S4C_Color pointer and prints it to stdout.
 *
 * @param color The color to debug.
 */
void debug_s4c_color(S4C_Color* color)
{
    debug_s4c_color_2file(color,stdout);
}

/**
 * Takes a char matrix (maximum line size is S4C_MAXCOLS), the height of each frame, the width of each frame, the S4C_Color palette pointer and the palette size.
 * Contructs and returns an S4C_Sprite with its fields using the passed arguments.
 * @param data The char matrix to wrap.
 * @param frameheight The height of each frame.
 * @param framewidth The width of each frame.
 * @param palette The pointer to s4c color palette/array.
 * @param palette_size The size of s4c color palette/array.
 */
S4C_Sprite s4c_new_sprite(char data[][S4C_MAXCOLS], int frameheight, int framewidth, S4C_Color* palette, int palette_size)
{
    S4C_Sprite res = {0};
    res.frame_height = frameheight;
    res.frame_width = framewidth;
    res.palette = palette;
    res.palette_size = palette_size;
    for (int i = 0; i < frameheight; i++) {
        for (int j = 0; j < framewidth; j++) {
            res.data[i][j] = data[i][j];
        }
    }
    return res;
}

#ifndef S4C_RAYLIB_EXTENSION

/**
 * Initialises a color pair from a passed S4C_Color pointer.
 * @param palette The S4C_Color pointer array at hand.
 * @param color_index The resulting color index for defined colorpair.
 * @param bg_color_index The color index for background color of defined colorpair. Typical values are 0 or, only after use_default_colors(), -1.
 */
void init_s4c_color_pair_ex(S4C_Color* color, int color_index, int bg_color_index)
{

    if (color == NULL) {
        fprintf(stderr,"Error: invalid S4C_Color at %s().",__func__);
        exit(EXIT_FAILURE);
    }

    int r, g, b;
    char color_name[50];

    r = color->red;
    g = color->green;
    b = color->blue;
    strcpy(color_name,color->name);

    int proportional_r = (((float)r + 1.0) / 256)*1000;
    int proportional_g = (((float)g + 1.0) / 256)*1000;
    int proportional_b = (((float)b + 1.0) / 256)*1000;
    init_color(color_index, proportional_r, proportional_g, proportional_b);
    init_pair(color_index, color_index, bg_color_index);
}

/**
 * Initialises a color pair from a passed S4C_Color pointer.
 * The background color index for the defined color pair is 0.
 * @param palette The S4C_Color pointer array at hand.
 * @param color_index The resulting color index for defined colorpair.
 */
void init_s4c_color_pair(S4C_Color* color, int color_index)
{
    init_s4c_color_pair_ex(color, color_index, 0);
}

/**
 * Initialises a color pair from a passed S4C_Color pointer.
 * It sets the background color index for the pair to -1.
 * This is useless to any curses implementation that does not support use_default_colors().
 * In that case, plain init_s4c_color_pair() should be used.
 * @param palette The S4C_Color pointer array at hand.
 * @param color_index The resulting color index for defined colorpair.
 */
void init_s4c_color_pair_default_bg(S4C_Color* color, int color_index)
{
    init_s4c_color_pair_ex(color, color_index, -1);
}

#endif

const char* s4c_color_strings[S4C_MAX_COLOR_INDEX+1] = {
    "S4C_BLACK",
    "S4C_RED",
    "S4C_BRIGHT_GREEN",
    "S4C_BRIGHT_YELLOW",
    "S4C_BLUE",
    "S4C_MAGENTA",
    "S4C_CYAN",
    "S4C_WHITE",
    "S4C_ORANGE",
    "S4C_LIGHT_BROWN",
    "S4C_DARK_BROWN",
    "S4C_PURPLE",
    "S4C_DARK_GREEN",
    "S4C_GREY",
    "S4C_LIGHT_YELLOW",
    "S4C_LIGHT_BLUE",
    "S4C_DARK_YELLOW",
    "S4C_DARK_OLIVE",
    "S4C_LIGHT_OLIVE",
    "S4C_OLIVE",
    "S4C_DARK_CHERRY",
    "S4C_LIGHT_CHERRY",
    "S4C_CHERRY",
    "S4C_SALMON",
    "S4C_DARK_BLUE",
    "S4C_VIOLET",
    "S4C_INDIGO",
    "S4C_LIGHT_ORANGE",
    "S4C_TEAL",
    "S4C_DARK_CYAN",
    "S4C_DARK_PURPLE",
    "S4C_LIGHT_PURPLE",
};

const char* s4c_color_name(S4C_Color_Index color_index)
{
    if (color_index < S4C_MIN_COLOR_INDEX || color_index > S4C_MAX_COLOR_INDEX) {
        fprintf(stderr,"[%s]:  Invalid color index { %i }, { %s -> [%i] }.", __func__, color_index, (color_index < S4C_MIN_COLOR_INDEX ? "Below min valid value " : "Above max valid value"), (color_index < S4C_MIN_COLOR_INDEX ? S4C_MIN_COLOR_INDEX : S4C_MAX_COLOR_INDEX));
        abort();
    }
    return s4c_color_strings[color_index-S4C_MIN_COLOR_INDEX];
}

#ifndef S4C_RAYLIB_EXTENSION
/**
 * Initialises all the needed color pairs for animate, from the palette file.
 * @param palette The palette file to read the colors from.
 */
void init_s4c_color_pairs(FILE* palette)
{

    char line[S4C_MAX_LINE_LENGTH];
    int color_index = 9;

    while (fgets(line, S4C_MAX_LINE_LENGTH, palette) != NULL) {
        // Check if the line starts with "#", "GIMP Palette", "Name:" or "Columns:"
        if (strncmp(line, "#", 1) == 0 || strncmp(line, "GIMP Palette", 12) == 0 ||
            strncmp(line, "Name:", 5) == 0 || strncmp(line, "Columns:", 8) == 0) {
            // Skip the comment or irrelevant line
            continue;
        }

        // Parse the color values and name
        int r, g, b;
        char name[S4C_PALETTEFILE_MAX_COLOR_NAME_LEN];
        if (sscanf(line, "%d %d %d %[^\n]", &r, &g, &b, name) != 4) {
            fprintf(stderr, "[%s]  Error: could not parse palette line: %s\n", __func__, line);
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
 * Demoes all colors supported by the palette in the passed WINDOW. Not guaranteed to work.
 * Since it uses indexes defined by default from animate.h, it should work only when your currently initialised palette has color pairs for the expected index range.
 * @param win The window to print the demo to.
 */
void test_s4c_color_pairs(WINDOW* win)
{
    for (int i = S4C_MIN_COLOR_INDEX; i < S4C_MAX_COLOR_INDEX +1; i++) {
        int color_index = i;
        if (color_index >= 0 && color_index < S4C_MAX_COLORS) {
            wattron(win, COLOR_PAIR(color_index));
            mvwaddch(win, 2, 2+i-S4C_MIN_COLOR_INDEX, ' ' | A_REVERSE);
            wattroff(win, COLOR_PAIR(color_index));
        }
    }

    wrefresh(win);
    refresh();
}

int s4c_check_has_colors(void)
{
    if (has_colors() == FALSE) {
        return  S4C_ERR_TERMCOLOR;
    }
    return 0;
}

int s4c_check_can_change_color(void)
{
    if (can_change_color() == FALSE) {
        return S4C_ERR_TERMCHANGECOLOR;
    }
    return 0;
}

/**
 * Checks terminal color capabilities.
 * @return 0 if successful, a negative value otherwise.
 */
int s4c_check_term(void)
{

    bool curses_was_ready = (stdscr != NULL) ? true : false;

    if (!curses_was_ready) { //We temporarily try to start curses ourselves.
        setlocale(LC_ALL, "");
        initscr();
        clear();
        refresh();
        start_color();
    }

    int checks[2] = {0};

    checks[0] = s4c_check_has_colors();
    checks[1] = s4c_check_can_change_color();
    if (checks[0] != 0) {
        if (!curses_was_ready) {
            endwin();
        }
        return checks[0];
    }
    if (checks[1] != 0) {
        if (!curses_was_ready) {
            endwin();
        }
        return checks[1];
    }
    if (!curses_was_ready) {
        endwin();
    }
    return 0;
}

/**
 * Checks window size using s4c_animate() logic check.
 * @param win The window to check.
 * @param rows Height of animation.
 * @param cols Width of animation.
 * @param startX The X coord we want to draw at.
 * @param startY The Y coord we want to draw at.
 * @return 0 if successful, a negative value otherwise.
 */
int s4c_check_win(WINDOW* win, int rows, int cols, int startX, int startY)
{
    // Check if window is big enough
    int win_rows, win_cols;
    getmaxyx(win, win_rows, win_cols);

    if (win_rows < rows + startY || win_cols < cols + startX) {
        return S4C_ERR_SMALL_WIN;
    }
    return 0;
}

/**
 * Demoes color pairs defined in s4c to the passed window.
 * Since it uses indexes defined by default from animate.h, it should work only when your currently initialised palette has color pairs for the expected index range.
 * @param win The Window pointer to print to.
 * @param colors_per_row How many colors to print in each row.
 */
void slideshow_s4c_color_pairs(WINDOW* win)
{
    if (win == NULL) {
        fprintf(stderr,"[%s]:  Passed Window was NULL.",__func__);
        abort();
    }
    int cursorCheck = curs_set(0); // We try making the cursor invisible

    if (cursorCheck == ERR) {
        //TODO
        //Log this
        //fprintf(stderr,"animate => Terminal does not support cursor visibility state.\n");
    }

    // Get window max size
    int win_rows, win_cols;
    getmaxyx(win, win_rows, win_cols);

    int picked = 0;
    int quit = 0;
    int c = -1;
    wrefresh(win);
    refresh();

    int color_index = S4C_MIN_COLOR_INDEX;

    do {
        if (color_index >= 0) {
            wattron(win,COLOR_PAIR(color_index));
            for (int i=0; i<win_rows; i++) {
                for (int j=0; j<win_cols; j++) {
                    mvwaddch(win, i, j, ' ' | A_REVERSE);
                }
            }
            wattroff(win,COLOR_PAIR(color_index));
            if (win_cols > S4C_MAX_COLOR_NAME_LEN+9) {
                mvwprintw(win, 2, 1, "[%i] [%s]", color_index, s4c_color_name(color_index));
            } else if (win_cols > 5) {
                mvwprintw(win, 1, 1, "[%i]", color_index);
            }
            box(win,0,0);
            wrefresh(win);
            refresh();
        }
        c = wgetch(win);
        switch(c) {
        case 'q': { /*Enter*/
            quit = 1;

        };
        case 10: { /*Enter*/
            picked = 1;
        };
        break;
        case KEY_RIGHT: {
            color_index = (color_index == S4C_MAX_COLOR_INDEX ? color_index : color_index+1);

        };
        break;
        case KEY_LEFT: {
            color_index = (color_index == S4C_MIN_COLOR_INDEX ? color_index : color_index-1);

        };
        break;
        default: {
            //fprintf(stderr,"[%s]:  Unexpected int [%i].\n",__func__,c);
        }
        break;
        }
    } while(!quit && !picked);
}

/**
 * Takes a string and a int and prints it in curses sdtscr at the y value passed as line_num.
 * @param line The string to print
 * @param line_num The y value to print at in win
 * @param line_len The length of line to print
 * @param startX X coord of the win to start printing to.
 */
void s4c_print_spriteline(WINDOW* win, char* line, int curr_line_num, int line_length, int startX)
{
    for (int i = 0; i < line_length; i++) {
        char c = line[i];
        int color_index = c - '0' + 8;
        if (color_index >= 0 && color_index < S4C_MAX_COLORS) {
            wattron(win, COLOR_PAIR(color_index));
            mvwaddch(win, curr_line_num, startX + 1 + i, ' ' | A_REVERSE);
            wattroff(win, COLOR_PAIR(color_index));
        }

    }
}

/**
 * Calls s4c_animate_sprites_at_coords() with 0,0 as starting coordinates.
 * Not interrupt-safe. Receiving SIGINT while actively waiting on a frame with napms() will crash the program.
 * @see s4c_animate_sprites_at_coords()
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
int s4c_animate_sprites(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth)
{
    return s4c_animate_sprites_at_coords(sprites, w,repetitions, frametime, num_frames, frameheight, framewidth, 0, 0);
}

/**
 * Takes a WINDOW pointer to print into and a string for the file passed.
 * Takes a pre-initialised array of sprites, valid format output by sprites.py or sheet_converter.py.
 * Color-character map is define in s4c_print_spriteline().
 * Sets all the frames to the passed array.
 * Not interrupt-safe. Receiving SIGINT while actively waiting on a frame with napms() will crash the program.
 * @see s4c_print_spriteline()
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
int s4c_animate_sprites_at_coords(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], WINDOW* w, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY)
{
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
        for (int i=0; i<num_frames+1; i++) {
            box(w,0,0);
            for (int j=0; j<rows; j++) {
                // Print current frame
                s4c_print_spriteline(w,sprites[i][j], j+startY+1, cols, startX);
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
 * Not interrupt-safe. Receiving SIGINT while actively waiting on a frame with napms() will crash the program.
 * @param args_ptr Pointer to be cast to animate_args*.
 * @see animate_args
 */
void *s4c_animate_sprites_thread_at(void *args_ptr)
{

    animate_args* args = (animate_args *)args_ptr;
    WINDOW* w = args->win;
    int frametime = args->frametime;
    int num_frames = args->num_frames;
    int frameheight = args->frameheight;
    int framewidth = args->framewidth;
    int startX = args->startX;
    int startY = args->startY;

    int cursorCheck = curs_set(0); // We make the cursor invisible or return early with the error

    if (cursorCheck == ERR) {
        //return S4C_ERR_CURSOR; //fprintf(stderr,"animate => Terminal does not support cursor visibility state.\n");
        return NULL; // FIXME: should maybe return a meaningful constant pointer denoting the specific error?
    }

    int rows = frameheight;
    int cols = framewidth;

    // Check if window is big enough
    int win_rows, win_cols;
    getmaxyx(w, win_rows, win_cols);
    if (win_rows < rows + startY || win_cols < cols + startX) {
        fprintf(stderr, "[%s]  animate => Window is too small to display the sprite.\n",__func__);
        pthread_exit(NULL);
    }
    // Open the palette file and read the color values and names
    FILE* palette_file;
    palette_file = fopen("palette.gpl", "r");
    if (palette_file == NULL) {
        fprintf(stderr, "[%s]  Error: could not open palette file.\n",__func__);
        pthread_exit(NULL);
    }

    // Initialize all the colors and close palette file
    init_s4c_color_pairs(palette_file);

    // Run the animation thread loop
    do {
        for (int i=0; i<num_frames+1; i++) {
            box(w,0,0);
            if (args->stop_thread == 1) {
                break;
            }
            for (int j=0; j<rows; j++) {
                if (args->stop_thread == 1) {
                    break;
                }
                // Print current line for current frame
                s4c_print_spriteline(w,(args->sprites)[i][j], j+startY+1, cols, startX);
            }
            wrefresh(w);
            // Refresh the screen
            napms(frametime);
        };
    } while ( args->stop_thread != 1);

    // We make the cursor normal again
    curs_set(1);

    pthread_exit(NULL);
    //FIXME
    //Is this a bug? Do we have to return NULL here?
#ifdef _WIN32
    return NULL;
#endif
}

/**
 * Takes a WINDOW pointer to print into.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Uses the passed sprites and displays a range of them in the passed window if it is big enough.
 * Color-character map is define in s4c_print_spriteline().
 * Not interrupt-safe. Receiving SIGINT while actively waiting on a frame with napms() will crash the program.
 * @see s4c_print_spriteline()
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
int s4c_animate_rangeof_sprites_at_coords(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], WINDOW* w, int fromFrame, int toFrame, int repetitions, int frametime, int num_frames, int frameheight, int framewidth, int startX, int startY)
{
    //Validate requested range
    if (fromFrame < 0 || toFrame < 0 || fromFrame > toFrame || toFrame > num_frames ) {
        return S4C_ERR_RANGE;
    }

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
        //+1 to include toFrame index
        for (int i=fromFrame; i<toFrame+1 ; i++) {
            box(w,0,0);
            for (int j=0; j<rows; j++) {
                // Print current frame
                s4c_print_spriteline(w,sprites[i][j], j+startY+1, cols, startX);
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
 * Takes a WINDOW pointer to print into and an animation array, plus the index of requested frame to print.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * It checks if the passed WINDOW is big enough for the requested frame.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
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
int s4c_display_sprite_at_coords_checked(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY)
{
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
        s4c_print_spriteline(w,sprites[sprite_index][j], j+startY+1, cols, startX);
    }
    box(w,0,0);
    wrefresh(w);
    return 1;
}

/**
 * Takes a WINDOW pointer to print into and an animation array, plus the index of requested frame to print.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * It does not check if the passed WINDOW is big enough for the requested frame.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
 * @param sprites The sprites array.
 * @param sprite_index The index of requested sprite.
 * @param w The window to print into.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @return 1 if successful, a negative value for errors.
 */
int s4c_display_sprite_at_coords_unchecked(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY)
{
    //Validate requested range
    if (sprite_index < 0 || sprite_index > num_frames ) {
        return S4C_ERR_RANGE;
    }

    for (int j=0; j<frameheight; j++) {
        // Print current frame
        s4c_print_spriteline(w,sprites[sprite_index][j], j+startY+1, framewidth, startX);
    }
    box(w,0,0);
    wrefresh(w);
    return 1;
}

/**
 * Takes a WINDOW pointer to print into and an animation array, plus the index of requested frame to print.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Depending on if S4C_UNCHECKED is defined, it may or may not check if the passed WINDOW is big enough
 * for the requested frame.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
 * @param sprites The sprites array.
 * @param sprite_index The index of requested sprite.
 * @param w The window to print into.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @return 1 if successful, a negative value for errors.
 */
int s4c_display_sprite_at_coords(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], int sprite_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY)
{
#ifdef S4C_UNCHECKED
    return s4c_display_sprite_at_coords_unchecked(sprites, sprite_index, w, num_frames, frameheight, framewidth, startX, startY);
#else
    return s4c_display_sprite_at_coords_checked(sprites, sprite_index, w, num_frames, frameheight, framewidth, startX, startY);
#endif // S4C_UNCHECKED
}

#ifdef S4C_EXPERIMENTAL
/**
 * Takes an S4C_Animation pointer as src and a WINDOW pointer to print into, plus the index of requested frame to print.
 * Contrary to other of these functions, this one does not touch cursor settings.
 * Color-character map is define in s4c_print_spriteline().
 * @see s4c_print_spriteline()
 * @param src The S4C_Animation pointer used as source.
 * @param frame_index The index of requested frame.
 * @param w The window to print into.
 * @param num_frames How many frames the animation will have.
 * @param frameheight Height of the frame.
 * @param framewidth Width of the frame.
 * @param startY Y coord of the window to start printing to.
 * @param startY X coord of the window to start printing to.
 * @see S4C_ERR_SMALL_WIN
 * @return 1 if successful, a negative value for errors.
 */
int s4c_display_frame(S4C_Animation* src, int frame_index, WINDOW* w, int num_frames, int frameheight, int framewidth, int startX, int startY)
{

    char*** anim = *src;
    //Validate requested range
    if (frame_index < 0 || frame_index > num_frames ) {
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
        s4c_print_spriteline(w,anim[frame_index][j], j+startY+1, cols, startX);
    }
    box(w,0,0);
    wrefresh(w);
    return 1;
}

/**
 * Takes a source animation vector matrix and a dinamyc array destination to copy to.
 * Takes ints to indicate how many frames, rows per frame and cols per row to copy.
 * Allocates the needed memory for the destination.
 * @param frames How many frames to copy.
 * @param rows How many rows to copy.
 * @param cols How many cols to copy.
 * @param source The source sprites array.
 * @param dest The destination sprites array.
 */
void s4c_copy_animation_alloc(S4C_Animation* dest, char source[][S4C_MAXROWS][S4C_MAXCOLS], int frames, int rows, int cols)
{
    if (rows > MAXROWS) {
        fprintf(stderr,"{s4c} Error at [%s]: rows number was bigger than S4C_MAXROWS: [%i > %i]\n",__func__,rows,S4C_MAXROWS);
        exit(EXIT_FAILURE);
    }
    if (cols > MAXCOLS) {
        fprintf(stderr,"{s4c} Error at [%s]: cols number was bigger than S4C_MAXCOLS: [%i > %i]\n",__func__,cols,S4C_MAXCOLS);
        exit(EXIT_FAILURE);
    }
    *dest = malloc(frames * sizeof(char**));
    for (int i = 0; i < frames; i++) {
        (*dest)[i] = malloc(rows * sizeof(char*));
        for (int j = 0; j < rows; j++) {
            (*dest)[i][j] = malloc(cols * sizeof(char));
            for (int k = 0; k < cols; k++) {
                (*dest)[i][j][k] = source[i][j][k];
            }
        }
    }
}

/**
 * Takes an S4C_Animation pointer and frees it.
 * Takes ints to indicate how many frames, rows per frame to free.
 * @param animation The S4C_Animation pointer to free.
 * @param frames How many frames to free.
 * @param rows How many rows to free.
 */
void s4c_free_animation(S4C_Animation* animation, int frames, int rows)
{
    if (animation == NULL || *animation == NULL) {
        return; // Nothing to free if the pointer or animation is NULL
    }

    char*** anim = *animation;

    for (int i = 0; i < frames; i++) {
        for (int j = 0; j < rows; j++) {
            free(anim[i][j]);
        }
        free(anim[i]);
    }

    free(anim);
    *animation = NULL; // Set the pointer to NULL after freeing the memory
}

#endif //S4C_EXPERIMENTAL
#endif

/**
 * Takes an empty 3D char array (frame, height, width) and a file to read the sprites from.
 * Checks if the file version is compatible with the current reader version, otherwise returns a negative error value.
 * Closes file pointer before returning.
 * File format should have a sprite line on each line.
 * Sets all the frames to the passed array.
 * @param sprites The char array to fill with all the frames.
 * @param f The file to read the sprites from.
 * @param frames The number of frames to load.
 * @param rows The number of rows in each sprite.
 * @param columns The number of columns in each sprite.
 * @see S4C_ERR_FILEVERSION
 * @see S4C_ERR_LOADSPRITES
 * @see S4C_FILEFORMAT_VERSION
 * @return A negative error value if loading fails or the number of sprites read.
 */
int s4c_load_sprites(char sprites[][S4C_MAXROWS][S4C_MAXCOLS], FILE* f, int frames, int rows, int columns)
{

    if (frames == 0) {
        return 0;
    }

    char line[1024];
    char* file_version;
    char* token;
    const char* READER_VERSION = S4C_FILEFORMAT_VERSION;
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

        if (frame == frames) {
            break;
        }

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
 * Takes a source animation vector matrix and a destination to copy to.
 * Takes ints to indicate how many frames, rows per frame and cols per row to copy.
 * @param frames How many frames to copy.
 * @param rows How many rows to copy.
 * @param cols How many cols to copy.
 * @param source The source sprites array.
 * @param dest The destination sprites array.
 */
void s4c_copy_animation(char source[][S4C_MAXROWS][S4C_MAXCOLS], char dest[S4C_MAXFRAMES][S4C_MAXROWS][S4C_MAXCOLS], int frames, int rows, int cols)
{
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

#ifdef S4C_RAYLIB_EXTENSION

/**
 * Demoes all colors supported by the palette in the passed area.
 * Since it uses indexes defined by default from animate.h, it should work only when your currently initialised palette has color pairs for the expected index range.
 * @param area The area to draw the demo to.
 * @param palette The s4c color array palette.
 * @return true on success, false on errors
 */
bool test_s4c_color_pairs(Rectangle* area, S4C_Color* palette)
{
    if (!area) {
        fprintf(stderr,"%s():    Area is NULL.\n", __func__);
        return false;
    }
    int row = 5;
    float scale_factor = sqrt(area->width * area->height);
    float eps_factor = 0.03;
    float size_factor = eps_factor * scale_factor;
    int size = 1.5 * size_factor;
    if (area->width < (5 * size)) {
        fprintf(stderr,"%s():    Area is too small for width. --> {%f < %i}\n", __func__, area->width, 5*size);
        return false;
    }
    float min_h = (((S4C_MAX_COLOR_INDEX/row)+2) * size);
    if (area->height < min_h) {
        fprintf(stderr,"%s():    Area is too small for height. --> {%f < %f}\n", __func__, area->height, min_h);
        return false;
    }
    BeginDrawing();
    ClearBackground(ColorFromS4CPalette(palette,S4C_BLACK));
    int line = 0;
    for (int i = S4C_MIN_COLOR_INDEX; i < S4C_MAX_COLOR_INDEX +1; i++) {
        int color_index = i;
        if ( i % row == 0 ) {
            line++;
        }
        if (color_index >= 0 && color_index < S4C_MAX_COLORS) {
            DrawRectangle(area->x + (((i-S4C_MIN_COLOR_INDEX)%row) * size), area->y + (line) * size, size, size, ColorFromS4CPalette(palette, color_index));
        }
    }
    int fontSize = 20;
    DrawText("[ Press ENTER or TAP to quit ]", 14, (line+2) * size, fontSize, ColorFromS4CPalette(palette,S4C_RED));
    EndDrawing();
    return true;
}

/**
 * Takes an S4C_Color and returns the equivalent Color with 255 alpha.
 * @param c The S4C_Color to convert.
 * @return The converted Color.
 * @see ColorFromPaletteIdx()
 * @see S4C_Color
 */
Color color_from_s4c_color(S4C_Color c)
{
    return CLITERAL(Color) {
        c.red, c.green, c.blue, 255
    };
}

/**
 * Takes a string, the Y coordinate to draw at, the lenght of the line, the starting X position, the pixel size (square side), the S4C_Color palette pointer and the palette size.
 * Calls DrawRectangle() passing the converted color, by calling color_from_s4c_color().
 * @param line The string to draw.
 * @param coordY The Y coordinate to draw at.
 * @param line_length The length of the string to draw.
 * @param startX The starting X position to draw at.
 * @param pixelSize The size for each pixel's square.
 * @param palette The pointer to s4c color palette/array.
 * @param palette_size The size of s4c color palette/array.
 * @see color_from_s4c_color()
 */
void s4rl_draw_spriteline(char* line, int coordY, int line_length, int startX, int pixelSize, S4C_Color* palette, int palette_size)
{
    for (int i = 0; i < line_length; i++) {
        const char c = line[i];
        int color_index = c - '1';
        Color color;
        if (color_index < 0 || color_index > palette_size) {
#ifndef S4C_RL_QUIETER
            fprintf(stderr,"%s():    Can't print at [x: %i, y: %i], invalid color index -> {%i}. Palette size: {%i}. Using BLACK instead.\n", __func__, (startX + i), coordY, color_index, palette_size);
#endif // S4C_RL_QUIETER
            color = BLACK;
        } else {
            color = color_from_s4c_color(palette[color_index]);
        }
        DrawRectangle(startX + (i * (pixelSize)), coordY, pixelSize, pixelSize, color);
    }
}

/**
 * Takes a char matrix (maximum line size is S4C_MAXCOLS), the height of each frame, the width of each frame, the X and Y coordinates to draw at, the pixel size (square side), the S4C_Color palette pointer and the palette size.
 * Calls s4rl_draw_spriteline on each line of the passed frame.
 * @param sprite The char matrix to draw.
 * @param frameheight The height of each frame.
 * @param framewidth The width of each frame.
 * @param startX The X coordinate of upper-left corner of animation rectangle.
 * @param startY The Y coordinate of upper-left corner of animation rectangle.
 * @param pixelSize The size for each pixel's square.
 * @param palette The pointer to s4c color palette/array.
 * @param palette_size The size of s4c color palette/array.
 * @see s4rl_draw_spriteline()
 */
void s4rl_draw_sprite_at_coords(char sprite[][S4C_MAXCOLS], int frameheight, int framewidth, int startX, int startY, int pixelSize, S4C_Color* palette, int palette_size)
{

    int rows = frameheight;
    int cols = framewidth;

    // TODO: Check if window is big enough
    //int win_rows, win_cols;
    //getmaxyx(w, win_rows, win_cols);
    //if (win_rows < rows + startY || win_cols < cols + startX) {
    //	return S4C_ERR_SMALL_WIN; //fprintf(stderr, "animate => Window is too small to display the sprite.\n");
    //}

    for (int j=0; j<rows; j++) {
        // Print current frame line
        s4rl_draw_spriteline(sprite[j], (j*(pixelSize)) + (startY), cols, startX, pixelSize, palette, palette_size);
    }
}

/**
 * Takes a char matrix (maximum line size is S4C_MAXCOLS), the Rectangle to print into, the height of each frame, the width of each frame, the pixel size (square side), the S4C_Color palette pointer and the palette size.
 * Calls s4rl_draw_sprite_at_coords() and checks if the wanted Rectangle is big enough for the wanted animation.
 * @param sprite The char matrix to draw.
 * @param rect The Rectangle to print into.
 * @param frameheight The height of each frame.
 * @param framewidth The width of each frame.
 * @param pixelSize The size for each pixel's square.
 * @param palette The pointer to s4c color palette/array.
 * @param palette_size The size of s4c color palette/array.
 * @return 0 if successful, negative values otherwise.
 * @see s4rl_draw_sprite_at_coords()
 */
int s4rl_draw_sprite_at_rect(char sprite[][S4C_MAXCOLS], Rectangle rect, int frameheight, int framewidth, int pixelSize, S4C_Color* palette, int palette_size)
{
    float r_x = rect.x;
    float r_y = rect.y;
    float r_w = rect.width;
    float r_h = rect.height;
    int sanity = 0;
    if (frameheight * pixelSize > r_h) {
        fprintf(stderr,"%s():    Requested animation doesn't fit target Rectangle height, for given pixelsize {%i}. {%i > %f}\n", __func__, pixelSize, frameheight, r_h);
        sanity = S4C_ERR_SMALL_WIN;
    } else if (framewidth * pixelSize > r_w) {
        fprintf(stderr,"%s():    Requested animation doesn't fit target Rectangle width, for given pixelsize {%i}. {%i > %f}\n", __func__, pixelSize, framewidth, r_w);
        sanity = S4C_ERR_SMALL_WIN;
    }
    if (sanity != 0) {
        return sanity;
    } else {
        s4rl_draw_sprite_at_coords(sprite, frameheight, framewidth, r_x, r_y, pixelSize, palette, palette_size);
        return 0;
    }
}

/**
 * Takes a char matrix, the Rectangle to print into, a Vector for frame dimensions, the pixel size (square side), the S4C_Color palette pointer and the palette size.
 * Calls s4rl_draw_sprite_at_rect().
 * @param sprite The S4C_Sprite to draw.
 * @param rect The Rectangle to print into.
 * @param framesize The Vector2 for frame dimensions.
 * @param pixelSize The size for each pixel's square.
 * @param palette The pointer to s4c color palette/array.
 * @param palette_size The size of s4c color palette/array.
 * @return 0 if successful, negative values otherwise.
 * @see s4rl_draw_sprite_at_rect()
 */
int s4rl_draw_sprite_at_rect_V(char sprite[][S4C_MAXCOLS], Rectangle rect, Vector2 framesize, int pixelSize, S4C_Color* palette, int palette_size)
{
    return s4rl_draw_sprite_at_rect(sprite, rect, framesize.y, framesize.x, pixelSize, palette, palette_size);
}

/**
 * Takes a S4C_Sprite, the Rectangle to print into, and the pixel size (square side).
 * Calls s4rl_draw_sprite_at_rect().
 * @param sprite The S4C_Sprite to draw.
 * @param rect The Rectangle to print into.
 * @param pixelSize The size for each pixel's square.
 * @return 0 if successful, negative values otherwise.
 * @see s4rl_draw_sprite_at_rect()
 */
int s4rl_draw_s4c_sprite_at_rect(S4C_Sprite sprite, Rectangle rect, int pixelSize)
{
    return s4rl_draw_sprite_at_rect(sprite.data, rect, sprite.frame_height, sprite.frame_width, pixelSize, sprite.palette, sprite.palette_size);
}
#endif // S4C_RAYLIB_EXTENSION
#endif // S4C_ANIMATE_H

#ifdef S4C_GUI_H_

const char *string_s4c_gui_version(void)
{
    return S4C_GUI_API_VERSION_STRING;
}

int int_s4c_gui_version(void)
{
    return S4C_GUI_API_VERSION_INT;
}

s4c_gui_malloc_func* s4c_gui_inner_malloc = &S4C_GUI_MALLOC;
s4c_gui_calloc_func* s4c_gui_inner_calloc = &S4C_GUI_CALLOC;

#ifndef TEXT_FIELD_H_
#error "This should not happen. TEXT_FIELD_H_ is defined in s4c_gui.h"
#include "text_field.h"
#endif // TEXT_FIELD_H_

struct TextField_s {
#ifndef S4C_RAYLIB_EXTENSION
    WINDOW* win;
#else
    Rectangle area;
    Color box_color;
    Color txt_color;
    bool on;
#endif // S4C_RAYLIB_EXTENSION
    int height;
    int width;
    int start_x;
    int start_y;
    char* buffer;
    int length;
    int max_length;
    TextField_Full_Handler* handler;
    TextField_Linter** linters;
    size_t num_linters;
    const void** linter_args;
    char* prompt;
    s4c_gui_malloc_func* malloc_func;
    s4c_gui_calloc_func* calloc_func;
    s4c_gui_free_func* free_func;
};

TextField_Linter* default_linters[TEXTFIELD_DEFAULT_LINTERS_TOT+1] = {
    &lint_TextField_not_empty,
};

const void* default_linter_args[TEXTFIELD_DEFAULT_LINTERS_TOT+1] = {
    NULL,
};


#ifndef S4C_RAYLIB_EXTENSION
TextField new_TextField_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int start_x, int start_y, const char* prompt, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func)
#else
TextField new_TextField_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int start_x, int start_y, const char* prompt, Color box_color, Color txt_color, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func)
#endif // S4C_RAYLIB_EXTENSION
{
    assert(height>=0);
    assert(width>=0);
    assert(start_x>=0);
    assert(start_x>=0);
    TextField res = NULL;
    if (malloc_func != NULL) {
        res = malloc_func(sizeof(struct TextField_s));
        res->malloc_func = malloc_func;
        if (free_func != NULL) {
            res->free_func = free_func;
        }
        if (calloc_func != NULL) {
            res->calloc_func = calloc_func;
        } else {
            res->calloc_func = s4c_gui_inner_calloc;
        }
    } else {
        res->free_func = free;
        res->malloc_func = s4c_gui_inner_malloc;
        res->calloc_func = s4c_gui_inner_calloc;
        res = s4c_gui_inner_malloc(sizeof(struct TextField_s));
    }
    res->buffer = res->calloc_func(max_size+1, sizeof(char));
    memset(res->buffer, 0, max_size);
    if (prompt != NULL) {
        res->prompt = res->calloc_func(strlen(prompt)+1, sizeof(char));
        memcpy(res->prompt, prompt, strlen(prompt));
    }
    res->height = height;
    res->width = width;
    res->start_x = start_x;
    res->start_y = start_y;
#ifndef S4C_RAYLIB_EXTENSION
    res->win = newwin(height, width, start_y, start_x);
#else
    res->area = (Rectangle) {
        .x = start_x, .y = start_y, .height = height, .width = width
    };
    res->box_color = box_color;
    res->txt_color = txt_color;
#endif // S4C_RAYLIB_EXTENSION
    res->length = 0;
    res->max_length = max_size;
    res->handler = full_buffer_handler;
    res->num_linters = num_linters;
    if (linters != NULL && num_linters > 0) {
        // Alloc memory for the linter callbacks
        if (calloc_func != NULL) {
            res->linters = calloc_func(num_linters, sizeof(TextField_Linter*));
            res->calloc_func = calloc_func;
            if (free_func != NULL) {
                res->free_func = free_func;
            }
        } else {
            res->calloc_func = s4c_gui_inner_calloc;
            res->linters = s4c_gui_inner_calloc(num_linters, sizeof(TextField_Linter*));
        }
        res->linter_args = res->calloc_func(num_linters, sizeof(void*));
        for (size_t i=0; i < num_linters; i++) {
            if (linters[i] != NULL) {
                res->linters[i] = linters[i];
                res->linter_args[i] = linter_args[i];
            }
        }
    }
    return res;
}

#ifndef S4C_RAYLIB_EXTENSION
TextField new_TextField_centered_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int bound_x, int bound_y, const char* prompt, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func)
#else
TextField new_TextField_centered_(TextField_Full_Handler* full_buffer_handler, TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int bound_x, int bound_y, const char* prompt, Color box_color, Color txt_color, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func)
#endif // S4C_RAYLIB_EXTENSION
{
    int start_y = (bound_y - height) / 2;
    int start_x = (bound_x - width) / 2;
#ifndef S4C_RAYLIB_EXTENSION
    return new_TextField_(full_buffer_handler, linters, num_linters, linter_args, max_size, height, width, start_x, start_y, prompt, malloc_func, calloc_func, free_func);
#else
    return new_TextField_(full_buffer_handler, linters, num_linters, linter_args, max_size, height, width, start_x, start_y, prompt, box_color, txt_color, malloc_func, calloc_func, free_func);
#endif // S4C_RAYLIB_EXTENSION
}

TextField new_TextField(size_t max_size, int height, int width, int start_x, int start_y)
{
#ifndef S4C_RAYLIB_EXTENSION
    return new_TextField_(&warn_TextField, default_linters, TEXTFIELD_DEFAULT_LINTERS_TOT, default_linter_args, max_size, height, width, start_x, start_y, NULL, s4c_gui_inner_malloc, s4c_gui_inner_calloc, NULL);
#else
    return new_TextField_(&warn_TextField, default_linters, TEXTFIELD_DEFAULT_LINTERS_TOT, default_linter_args, max_size, height, width, start_x, start_y, NULL, WHITE, BLACK, s4c_gui_inner_malloc, s4c_gui_inner_calloc, NULL);
#endif // S4C_RAYLIB_EXTENSION
}

TextField new_TextField_centered(size_t max_size, int height, int width, int bound_x, int bound_y)
{
#ifndef S4C_RAYLIB_EXTENSION
    return new_TextField_centered_(&warn_TextField, default_linters, TEXTFIELD_DEFAULT_LINTERS_TOT, default_linter_args, max_size, height, width, bound_x, bound_y, NULL, s4c_gui_inner_malloc, s4c_gui_inner_calloc, NULL);
#else
    return new_TextField_centered_(&warn_TextField, default_linters, TEXTFIELD_DEFAULT_LINTERS_TOT, default_linter_args, max_size, height, width, bound_x, bound_y, NULL, WHITE, BLACK, s4c_gui_inner_malloc, s4c_gui_inner_calloc, NULL);
#endif // S4C_RAYLIB_EXTENSION
}

TextField new_TextField_linted(TextField_Linter** linters, size_t num_linters, const void** linter_args, size_t max_size, int height, int width, int start_x, int start_y)
{
#ifndef S4C_RAYLIB_EXTENSION
    return new_TextField_(&warn_TextField, linters, num_linters, linter_args, max_size, height, width, start_x, start_y, NULL, s4c_gui_inner_malloc, s4c_gui_inner_calloc, NULL);
#else
    return new_TextField_(&warn_TextField, linters, num_linters, linter_args, max_size, height, width, start_x, start_y, NULL, WHITE, BLACK, s4c_gui_inner_malloc, s4c_gui_inner_calloc, NULL);
#endif // S4C_RAYLIB_EXTENSION
}

TextField new_TextField_alloc(size_t max_size, int height, int width, int start_x, int start_y, s4c_gui_malloc_func* malloc_func, s4c_gui_calloc_func* calloc_func, s4c_gui_free_func* free_func)
{
#ifndef S4C_RAYLIB_EXTENSION
    return new_TextField_(&warn_TextField, default_linters, TEXTFIELD_DEFAULT_LINTERS_TOT, default_linter_args, max_size, height, width, start_x, start_y, NULL, malloc_func, calloc_func, free_func);
#else
    return new_TextField_(&warn_TextField, default_linters, TEXTFIELD_DEFAULT_LINTERS_TOT, default_linter_args, max_size, height, width, start_x, start_y, NULL, WHITE, BLACK, malloc_func, calloc_func, free_func);
#endif // S4C_RAYLIB_EXTENSION
}

void free_TextField(TextField txt_field)
{
    assert(txt_field!=NULL);
    // Clean up
#ifndef S4C_RAYLIB_EXTENSION
    delwin(txt_field->win);
#endif // S4C_RAYLIB_EXTENSION
    if (txt_field->malloc_func == malloc && txt_field->calloc_func == calloc) {
        if (txt_field->linters != NULL) {
            free(txt_field->linters);
            free(txt_field->linter_args);
        }
        free(txt_field->buffer);
        if (txt_field->prompt != NULL) {
            free(txt_field->prompt);
        }
        free(txt_field);
    } else {
        if (txt_field->free_func != NULL) {
            // TODO: Pseudo-free?
            txt_field->free_func(txt_field);
        }
        // Do nothing
    }
}

const char* get_TextField_value(TextField txt_field)
{
    assert(txt_field!=NULL);
    return txt_field->buffer;
}

bool lint_TextField(TextField txt_field)
{
    assert(txt_field!=NULL);
    bool res = true;
    TextField_Linter* linter_func = NULL;
    for (size_t i=0; res == true && i < txt_field->num_linters; i++) {
        linter_func = txt_field->linters[i];
        if (linter_func != NULL) {
            // NULL func being found don't affect the result
            res = linter_func(txt_field, txt_field->linter_args[i]);
        }
    }
    return res;
}

int get_TextField_len(TextField txt_field)
{
    assert(txt_field!=NULL);
    return txt_field->length;
}

#ifndef S4C_RAYLIB_EXTENSION
WINDOW* get_TextField_win(TextField txt_field)
{
    assert(txt_field!=NULL);
    return txt_field->win;
}

void draw_TextField(TextField txt)
{
    assert(txt!=NULL);
    // Draw a box around the window
    box(txt->win, 0, 0);
    if (txt->prompt != NULL) {
        if (txt->buffer[0] == '\0' && txt->width > strlen(txt->prompt)) {
            mvwprintw(txt->win, 1,1, "%s", txt->prompt);
        }
    }
    wrefresh(txt->win);
}
#else

Rectangle get_TextField_rec(TextField txt_field)
{
    assert(txt_field!=NULL);
    return txt_field->area;
}

/**
 * Draw function for TextField. If the underlying buffer gets too full, draws a hint to delete a char to the user.
 * @param txt The TextField to draw
 * @see update_TextField()
 */
void draw_TextField(TextField txt)
{
    assert(txt!=NULL);
    DrawRectangleRec(txt->area, txt->box_color);
    if (txt->on) {
        DrawRectangleLines(txt->area.x, txt->area.y, txt->width, txt->height, txt->txt_color);
        if (txt->prompt != NULL) {
            if (txt->buffer[0] == '\0') {
                DrawText(TextFormat("%s", txt->prompt), txt->start_x, txt->start_y, txt->width * 0.1f, txt->txt_color);
            } else {
                if (get_TextField_len(txt) < txt->max_length) {
                    DrawText(TextFormat("%s", txt->buffer), txt->start_x, txt->start_y, txt->width * 0.1f, txt->txt_color);
                } else {
                    DrawText("BACKSPACE to delete", txt->start_x, txt->start_y, txt->width* 0.1f, txt->txt_color);
                }
            }
        } else {
            if (txt->buffer[0] == '\0') {
            } else {
                if (get_TextField_len(txt) < txt->max_length) {
                    DrawText(TextFormat("%s", txt->buffer), txt->start_x, txt->start_y, txt->width * 0.1f, txt->txt_color);
                } else {
                    DrawText("BACKSPACE to delete", txt->start_x, txt->start_y, txt->width* 0.1f, txt->txt_color);
                }
            }
        }
    } else {
        if (txt->buffer[0] == '\0') {
            DrawText("HOVER to insert", txt->start_x, txt->start_y, txt->width* 0.1f, txt->txt_color);
        } else {
            if (get_TextField_len(txt) < txt->max_length) {
                DrawText(TextFormat("%s", txt->buffer), txt->start_x, txt->start_y, txt->width * 0.1f, txt->txt_color);
            } else {
                DrawText("BACKSPACE to delete", txt->start_x, txt->start_y, txt->width* 0.1f, txt->txt_color);
            }
        }
    }
}
#endif // S4C_RAYLIB_EXTENSION

void clear_TextField(TextField txt)
{
    assert(txt!=NULL);
    // Zero buffer and length
    memset(txt->buffer, 0, txt->max_length+1);
    txt->length = 0;
}

#ifndef S4C_RAYLIB_EXTENSION
void warn_TextField(TextField txt)
{
    assert(txt!=NULL);
    WINDOW* win = get_TextField_win(txt);
    // Buffer is full and user passed one more char. Discard it.
    wclear(win);
    box(win,0,0);
    mvwprintw(win, 1, 1, "%s", "Input is full.");
    mvwprintw(win, 2, 1, "%s", "Press Enter or Backspace.");
    wrefresh(win);
    napms(500);
    wclear(win);
    box(win,0,0);
    mvwprintw(win, 1, 1, "%s", get_TextField_value(txt));
    wrefresh(win);

}
#else
void warn_TextField(TextField txt)
{
    assert(txt!=NULL);
    Rectangle rec = get_TextField_rec(txt);

    DrawRectangleRec(rec, RED);
    DrawText("Input is full", rec.x, rec.y, rec.width / strlen("Input is full"), WHITE);
    DrawText("Press Enter or Backspace", rec.x, rec.y + (rec.width / strlen("Press Enter or Backspace")), rec.width / strlen("Press Enter or Backspace"), WHITE);
}
#endif // S4C_RAYLIB_EXTENSION

bool lint_TextField_not_empty(TextField txt, const void* unused)
{
    (void) unused;
    if (txt==NULL) return false;
    return txt->length>0;
}

bool lint_TextField_equals_cstr(TextField txt, const void* cstr)
{
    // Please, pass a null-terminated string.
    const char* str = (const char*) cstr;

    return (strcmp(get_TextField_value(txt), str) == 0);
}


bool lint_TextField_whitelist(TextField txt, const void* whitelist)
{
    // Please, pass a null-terminated string.
    const char* whitelist_cstr = (const char*) whitelist;
    size_t whitelist_size = strlen(whitelist);
    if (txt==NULL || whitelist == NULL) return false;
    bool res = true;
    for (size_t i=0; res == true && i < txt->length; i++) {
        for (size_t j=0; res == true && j < whitelist_size; j++) {
            res = (txt->buffer[i] != whitelist_cstr[j]);
        }
    }
    return res;
}

bool lint_TextField_char_range(TextField txt, int min, int max)
{
    if (txt==NULL) return false;
    if (min < 0 || max > CHAR_MAX) return false;
    bool res = true;
    char ch = -1;
    for (size_t i=0; res == true && i < txt->length; i++) {
        ch = txt->buffer[i];
        if (ch == '\0') {
            if (i != txt->length) {
                //TODO: mismatch on len?
            }
            break;
        }
        res = (ch >= min && ch > max);
    }
    return res;
}

bool lint_TextField_digits_only(TextField txt)
{
    if(txt==NULL) return false;
    return lint_TextField_char_range(txt, '0', '9');
}

bool lint_TextField_printable_only(TextField txt)
{
    if(txt==NULL) return false;
    return lint_TextField_char_range(txt, ' ', '~');
}

#ifndef S4C_RAYLIB_EXTENSION
static void get_userText(TextField txt_field)
{
    assert(txt_field!=NULL);
    char* buffer = txt_field->buffer;
    int* length = &(txt_field->length);
    WINDOW* win = txt_field->win;
    assert(win!=NULL);

    const int max_length = txt_field->max_length;

    const int input_start_x = 1;
    // Move the cursor to the input field position
    wmove(win, 1, input_start_x);

    // Get input from the user
    int ch;
    while ((ch = wgetch(win)) != '\n') {
        // Check for backspace
        if (ch == KEY_BACKSPACE || ch == '\b' || ch == 127) {
            if (*length > 0) {
                // Erase the character
                mvwaddch(win, 1, *length, ' ');
                wrefresh(win);
                // Move cursor back
                wmove(win, 1, *length);
                buffer[(*length)-1] = '\0';
                (*length)--;
                if (*length == 0 && txt_field->prompt != NULL) {
                    //Redraw prompt
                    mvwprintw(win, 1, 1, "%s", txt_field->prompt);
                    wmove(win, 1, input_start_x);
                }
            }
        } else {
            if (*length < max_length) {
                if (*length == 0) {
                    //Clear and rebox win on first char entered
                    wclear(win);
                    box(win, 0, 0);
                    wmove(win, 1, input_start_x);
                }
                // Echo the character
                waddch(win, ch);
                wrefresh(win);
                // Add it to the buffer
                buffer[(*length)++] = ch;
            } else {
                // Buffer is full
                if (txt_field->handler != NULL) {
                    txt_field->handler(txt_field);
                }
            }
        }
    }
}
#else
/**
 * Update function for TextField, gets keys from user in a loop and edits the underlying buffer.
 * Supports backspace and enter.
 * @param txt_field The TextField to update
 * @return True if user pressed KEY_ENTER
 * @see draw_TextField
 */
bool update_TextField(TextField txt_field)
{
    assert(txt_field!=NULL);
    char* buffer = txt_field->buffer;
    int* length = &(txt_field->length);
    Rectangle area = txt_field->area;

    const int max_length = txt_field->max_length;

    bool mouseOnText = false;

    if (CheckCollisionPointRec(GetMousePosition(), area)) mouseOnText = true;
    else mouseOnText = false;

    if (IsKeyPressed(KEY_ENTER)) { // User sent enter
        return true;
    }

    txt_field->on = mouseOnText;

    if (mouseOnText) {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0) {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (*length < max_length)) {
                buffer[*length] = (char)key;
                buffer[*length+1] = '\0'; // Add null terminator at the end of the string.
                (*length)++;
            }

            if (*length >= max_length) {
                // Buffer is full
                if (txt_field->handler != NULL) {
                    txt_field->handler(txt_field);
                }
            }

            key = GetCharPressed();  // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            (*length)--;
            if (*length < 0) *length = 0;
            buffer[*length] = '\0';
        }
    } else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    return false;
}
#endif // S4C_RAYLIB_EXTENSION

#ifndef S4C_RAYLIB_EXTENSION
void use_clean_TextField(TextField txt_field)
{
    assert(txt_field!=NULL);
    clear_TextField(txt_field);

    draw_TextField(txt_field);

    get_userText(txt_field);
    wclear(txt_field->win);
    wrefresh(txt_field->win);
}
#endif // S4C_RAYLIB_EXTENSION
// }
// TEXT_FIELD_H_


#ifndef TOGGLE_H_
#error "This should not happen. TOGGLE_H_ is defined in s4c_gui.h"
#include "toggle.h"
#endif // TOGGLE_H_

#ifndef S4C_RAYLIB_EXTENSION
static const int TOGGLE_MENU_DEFAULT_QUIT_KEY = KEY_F(1);
#else
static const int TOGGLE_MENU_DEFAULT_QUIT_KEY = KEY_F1;
#endif // S4C_RAYLIB_EXTENSION

static void cycle_toggle_state(Toggle *toggle)
{
    toggle->state.ts_state.current_state = (toggle->state.ts_state.current_state + 1) % toggle->state.ts_state.num_states;
}

ToggleMenu new_ToggleMenu_(Toggle* toggles, int num_toggles, ToggleMenu_Conf conf)
{
    size_t widest_label_size = 0;
    for (size_t i=0; i < num_toggles; i++) {
        size_t curr_size = strlen(toggles[i].label);
        if (curr_size > widest_label_size) widest_label_size = curr_size;
    }
    return (ToggleMenu) {
        .toggles = toggles,
        .num_toggles = num_toggles,
        .height = num_toggles+2,
        .width = widest_label_size+2,
        .start_x = conf.start_x,
        .start_y = conf.start_y,
        .boxed = conf.boxed,
        .quit_key = ((conf.quit_key < 0) ? TOGGLE_MENU_DEFAULT_QUIT_KEY : conf.quit_key),
        .statewin_height = conf.statewin_height,
        .statewin_width = conf.statewin_width,
        .statewin_start_x = conf.statewin_start_x,
        .statewin_start_y = conf.statewin_start_y,
        .statewin_boxed = conf.statewin_boxed,
        .statewin_label = conf.statewin_label,
        .key_up = conf.key_up,
        .key_right = conf.key_right,
        .key_down = conf.key_down,
        .key_left = conf.key_left,
#ifndef S4C_RAYLIB_EXTENSION
        .get_mouse_events = conf.get_mouse_events,
        .mouse_handler = conf.mouse_handler,
        .mouse_events_mask = conf.mouse_events_mask,
#endif // S4C_RAYLIB_EXTENSION
    };
}

#ifndef S4C_RAYLIB_EXTENSION
void default_ToggleMenu_mousehandler__(ToggleMenu toggle_menu, MEVENT* mouse_event)
{
    printw("[DEBUG] %s():    Got mouse event at {x: %i, y: %i, z: %i}\n", __func__, mouse_event->x, mouse_event->y, mouse_event->z);
    printw("[DEBUG] %s():    Info on menu: {\n", __func__);
    printw("[DEBUG]" ToggleMenu_Fmt "\n", ToggleMenu_Arg(toggle_menu));
    printw("[DEBUG] }\n");
    refresh();
    napms(2000);
}
#endif // S4C_RAYLIB_EXTENSION

static const ToggleMenu_Conf TOGGLE_MENU_DEFAULT_CONF = {
    .start_x = 0,
    .start_y = 0,
    .boxed = true,
    .quit_key = TOGGLE_MENU_DEFAULT_QUIT_KEY,
    .key_up = KEY_UP,
    .key_right = KEY_RIGHT,
    .key_down = KEY_DOWN,
    .key_left = KEY_LEFT,
};

ToggleMenu new_ToggleMenu(Toggle* toggles, int num_toggles)
{
    return new_ToggleMenu_(toggles, num_toggles, TOGGLE_MENU_DEFAULT_CONF);
}

#ifndef S4C_RAYLIB_EXTENSION
ToggleMenu new_ToggleMenu_with_mouse_mask(Toggle* toggles, int num_toggles, ToggleMenu_MouseEvent_Handler* mouse_events_handler, mmask_t mouse_events_mask)
{
    ToggleMenu res = new_ToggleMenu_(toggles, num_toggles, TOGGLE_MENU_DEFAULT_CONF);
    res.get_mouse_events = true;
    res.mouse_handler = mouse_events_handler;
    res.mouse_events_mask = mouse_events_mask;
    return res;
}

ToggleMenu new_ToggleMenu_with_mouse(Toggle* toggles, int num_toggles, ToggleMenu_MouseEvent_Handler* mouse_events_handler)
{
    return new_ToggleMenu_with_mouse_mask(toggles, num_toggles, mouse_events_handler, TOGGLEMENU_DEFAULT_MOUSEEVENTS_MASK);
}
#endif // S4C_RAYLIB_EXTENSION

void free_ToggleMenu(ToggleMenu toggle_menu)
{
    for (size_t i=0; i<toggle_menu.num_toggles; i++) {
        switch (toggle_menu.toggles[i].type) {
        case BOOL_TOGGLE:
        case MULTI_STATE_TOGGLE: {
            break;
        }
        case TEXTFIELD_TOGGLE: {
            free_TextField(toggle_menu.toggles[i].state.txt_state);
            break;
        }
        default: {
            //Unexpected
            assert(false);
            break;
        }
        }
    }
}

#ifndef S4C_RAYLIB_EXTENSION
void draw_ToggleMenu_states(WINDOW *win, ToggleMenu toggle_menu)
{

    Toggle* toggles = toggle_menu.toggles;
    int num_toggles = toggle_menu.num_toggles;
    // Clear the window
    wclear(win);

    if (toggle_menu.statewin_boxed) box(win, 0, 0);
    if (toggle_menu.statewin_label != NULL) mvwprintw(win, 0, 1, "%s", toggle_menu.statewin_label);

    // Print toggle states
    for (int i = 0; i < num_toggles; i++) {
        // Print toggle label
        mvwprintw(win, i + 1, 1, "%s:", toggles[i].label);

        // Print toggle state
        if (toggles[i].type == BOOL_TOGGLE) {
            mvwprintw(win, i + 1, 20, "[%s]", toggles[i].state.bool_state ? "ON" : "OFF");
        } else if (toggles[i].type == MULTI_STATE_TOGGLE) {
            if (toggles[i].multistate_formatter != NULL) {
                mvwprintw(win, i + 1, 20, "[%s]", toggles[i].multistate_formatter(toggles[i].state.ts_state.current_state));
            } else {
                mvwprintw(win, i + 1, 20, "[%d/%d]", toggles[i].state.ts_state.current_state, toggles[i].state.ts_state.num_states);
            }
        } else if (toggles[i].type == TEXTFIELD_TOGGLE) {
            mvwprintw(win, i + 1, 20, "%s", get_TextField_value(toggles[i].state.txt_state));
        }

        // Print lock indicator
        if (toggles[i].locked) {
            mvwprintw(win, i + 1, 30, "(LOCKED)");
        }
    }

    wrefresh(win);
}

void handle_ToggleMenu(ToggleMenu toggle_menu)
{
    bool try_display_state = false;
    WINDOW* state_win = NULL;
    if (toggle_menu.statewin_width > 0 && toggle_menu.statewin_height > 0) {
        try_display_state = true;
        // Create a window for toggle states
        state_win = newwin(toggle_menu.statewin_height, toggle_menu.statewin_width, toggle_menu.statewin_start_y, toggle_menu.statewin_start_x);
        if (toggle_menu.statewin_boxed) box(state_win, 0, 0);
        if (toggle_menu.statewin_label != NULL) mvwprintw(state_win, 0, 1, "%s", toggle_menu.statewin_label);
        wrefresh(state_win);
    }

    Toggle* toggles = toggle_menu.toggles;
    int num_toggles = toggle_menu.num_toggles;

    // Create MENU for toggles
    ITEM **toggle_items = (ITEM **)calloc(num_toggles + 1, sizeof(ITEM *));
    MENU *nc_menu;
    for (int i = 0; i < num_toggles; i++) {
        toggle_items[i] = new_item(toggles[i].label, "");
        if (toggles[i].type == MULTI_STATE_TOGGLE && !toggles[i].locked) {
            // Allow cycling through states for MULTI_STATE_TOGGLE toggles
            set_item_userptr(toggle_items[i], &toggles[i]);
        }
        if (toggles[i].type == BOOL_TOGGLE && !toggles[i].locked) {
            // Allow switching on bool toggle
            set_item_userptr(toggle_items[i], &toggles[i]);
        }
        if (toggles[i].type == TEXTFIELD_TOGGLE && !toggles[i].locked) {
            // Allow changing textfield toggle
            set_item_userptr(toggle_items[i], &toggles[i]);
        }
    }
    toggle_items[num_toggles] = NULL;
    nc_menu = new_menu(toggle_items);

    if (try_display_state) draw_ToggleMenu_states(state_win, toggle_menu);

    // Create a window for the MENU
    WINDOW *menu_win = newwin(toggle_menu.height, toggle_menu.width, toggle_menu.start_y, toggle_menu.start_x); //LINES/2, COLS / 2, 0, 0);
    keypad(menu_win, TRUE);
    set_menu_win(nc_menu, menu_win);
    set_menu_sub(nc_menu, derwin(menu_win, toggle_menu.height -1, toggle_menu.width -2, toggle_menu.start_y +1, toggle_menu.start_x+1)); //LINES/2) - 2, COLS / 2 - 2, 1, 1));
    set_menu_mark(nc_menu, "");
    if (toggle_menu.boxed) box(menu_win,0,0);
    if (toggle_menu.get_mouse_events) {
        mmask_t mouse_events_mask = toggle_menu.mouse_events_mask;
        mousemask(mouse_events_mask, NULL);
    }
    post_menu(nc_menu);
    wrefresh(menu_win);

    // Main loop
    int c;
    while ((c = wgetch(menu_win)) != toggle_menu.quit_key) {
        if ( c == toggle_menu.key_down) {
            int res = menu_driver(nc_menu, REQ_DOWN_ITEM);
            if (res == E_REQUEST_DENIED) {
                res = menu_driver(nc_menu, REQ_FIRST_ITEM);
            }
        } else if ( c == toggle_menu.key_up) {
            int res = menu_driver(nc_menu, REQ_UP_ITEM);
            if (res == E_REQUEST_DENIED) {
                res = menu_driver(nc_menu, REQ_LAST_ITEM);
            }
        } else if ( c == toggle_menu.key_right) {
            // Cycle through states for selected item
            if (current_item(nc_menu)) {
                Toggle *toggle = (Toggle *)item_userptr(current_item(nc_menu));
                if (toggle && toggle->type == MULTI_STATE_TOGGLE && !toggle->locked) {
                    cycle_toggle_state(toggle);
                    if (try_display_state) draw_ToggleMenu_states(state_win, toggle_menu);
                }
            }
        } else if ( c == toggle_menu.key_left) {
            // Cycle through states for selected item
            if (current_item(nc_menu)) {
                Toggle *toggle = (Toggle *)item_userptr(current_item(nc_menu));
                if (toggle && toggle->type == MULTI_STATE_TOGGLE && !toggle->locked) {
                    cycle_toggle_state(toggle);
                    if (try_display_state) draw_ToggleMenu_states(state_win, toggle_menu);
                }
            }
        } else if ( toggle_menu.get_mouse_events && (c == KEY_MOUSE) ) {
            MEVENT mouse_event;
            if (getmouse(&mouse_event) == OK) {
                if (wenclose(menu_win, mouse_event.y, mouse_event.x) == TRUE) {
                    assert(toggle_menu.mouse_handler != NULL);
                    toggle_menu.mouse_handler(toggle_menu, &mouse_event);
                }
            } else {
                //TODO: handle this failure somehow
                endwin();
                fprintf(stderr,"\n[DEBUG] %s():    Failed getmouse().\n", __func__);
                napms(2000);
                refresh();
            }
        } else if ( c == '\n') {
            // Toggle state for selected BOOL_TOGGLE item
            if (current_item(nc_menu)) {
                Toggle *toggle = (Toggle *)item_userptr(current_item(nc_menu));
                if (toggle && toggle->type == BOOL_TOGGLE && !toggle->locked) {
                    toggle->state.bool_state = !toggle->state.bool_state;
                    draw_ToggleMenu_states(state_win, toggle_menu);
                } else if (toggle && toggle->type == TEXTFIELD_TOGGLE && !toggle->locked) {
                    use_clean_TextField(toggle->state.txt_state);
                    if (try_display_state) draw_ToggleMenu_states(state_win, toggle_menu);
                }
            }
        }
    }

    // Clean up
    unpost_menu(nc_menu);
    free_menu(nc_menu);
    for (int i = 0; i < num_toggles; i++) {
        free_item(toggle_items[i]);
    }
    free(toggle_items);
    delwin(menu_win);
    if (try_display_state) delwin(state_win);
}
#else
void draw_ToggleMenu_states(Rectangle area, ToggleMenu toggle_menu)
{
    assert(false);
}

void update_ToggleMenu(ToggleMenu toggle_menu)
{
    assert(false);
    Toggle toggle = {0};
    cycle_toggle_state(&toggle);
}

void draw_ToggleMenu(ToggleMenu toggle_menu)
{
    assert(false);
}
#endif // S4C_RAYLIB_EXTENSION
// }
// TOGGLE_H_
#endif // S4C_GUI_H_
