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
#include "../src/s4c.h"

#ifdef S4C_GUI_H_
int textfield_main(void)
{
#ifndef S4C_RAYLIB_EXTENSION
    // Initialize ncurses
    initscr();
    cbreak(); // Disable line buffering
    noecho(); // Don't echo input to screen
#else
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "s4c demo_gui for raylib");
    SetTargetFPS(60);
#endif // S4C_RAYLIB_EXTENSION

    // Define the dimensions and position of the window
    int height = 5;
    int width = 30;

    TextField_Linter* my_linters[2] = {
        &lint_TextField_not_empty,
        &lint_TextField_equals_cstr,
    };

    const void* linter_args[2] = {
        NULL,
        "ciao",
    };

    size_t n_linters = 2;
    size_t max_size = 10;
    char* prompt = "Start typing";

#ifndef S4C_RAYLIB_EXTENSION
    TextField txt_field = new_TextField_centered_(&warn_TextField, my_linters, n_linters, linter_args, max_size, height, width, COLS, LINES, prompt, S4C_GUI_MALLOC, S4C_GUI_CALLOC, NULL);
#else
    TextField txt_field = new_TextField_centered_(&warn_TextField, my_linters, n_linters, linter_args, max_size, height*10, width*10, screenWidth, screenHeight, prompt, GRAY, RED, S4C_GUI_MALLOC, S4C_GUI_CALLOC, NULL);
#endif // S4C_RAYLIB_EXTENSION


#ifndef S4C_RAYLIB_EXTENSION
    use_clean_TextField(txt_field);
    // Print the input back to the screen
    mvprintw(LINES/2 +1, (COLS - strlen("You entered: ")) / 2, "You entered: %s", get_TextField_value(txt_field));
    mvprintw(LINES/2 +2, (COLS - strlen("len: ")) / 2, "len: %i", get_TextField_len(txt_field));
    mvprintw(LINES/2 +4, (COLS - strlen("Lint result: ")) / 2, "Lint result: %s", (lint_TextField(txt_field) ? "pass" : "fail"));
    refresh();

    // Wait for user input before exiting
    getch();
#else
    assert(txt_field != NULL);
    clear_TextField(txt_field);
    while (!WindowShouldClose()) {
        // Update
        if (update_TextField(txt_field)) {
            fprintf(stderr, "You entered: {%s}\n", get_TextField_value(txt_field));
            fprintf(stderr, "Len: {%i}\n", get_TextField_len(txt_field));
            fprintf(stderr, "Lint result: {%s}\n", (lint_TextField(txt_field) ? "pass" : "fail"));
        }
        BeginDrawing();
        // Draw
        ClearBackground(WHITE);
        draw_TextField(txt_field);
        EndDrawing();
    }
#endif // S4C_RAYLIB_EXTENSION

    free_TextField(txt_field);

#ifndef S4C_RAYLIB_EXTENSION
    endwin();
#else
    CloseWindow();
#endif // S4C_RAYLIB_EXTENSION

    return 0;
}

const char* my_format(int val)
{
    switch(val) {
    case 0: {
        return "zero";
    }
    break;
    case 1: {
        return "one";
    }
    break;
    case 2: {
        return "two";
    }
    break;
    default: {
        return "too high!";
    }
    break;
    }
}

int togglemenu_main(size_t argc, char** argv)
{
#ifndef S4C_RAYLIB_EXTENSION
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
#else
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "s4c demo_gui for raylib");
    SetTargetFPS(60);
#endif // S4C_RAYLIB_EXTENSION

    // Define the dimensions and position of the textfield window
    int height = 5;
    int width = 30;
#ifndef S4C_RAYLIB_EXTENSION
    int start_y = (LINES/2) +3;
#else
    int start_y = 2;
#endif // S4C_RAYLIB_EXTENSION
    int start_x = 2;

    size_t txt_max_size_1 = 10;
    size_t txt_max_size_2 = 15;

    const char* sidewin_label = "Toggle status:";

    const int MAX_STATES = 3;

    // Define menu options and their toggle states
    Toggle toggles[] = {
        {BOOL_TOGGLE, (ToggleState){.bool_state = true}, "[] Light(U)", false},
        {MULTI_STATE_TOGGLE, (ToggleState){.ts_state.current_state = 0, .ts_state.num_states = MAX_STATES}, "<Volume>(L)", true},
        {BOOL_TOGGLE, (ToggleState){.bool_state = false}, "[] Root (L)", true},
        {MULTI_STATE_TOGGLE, (ToggleState){.ts_state.current_state = 0, .ts_state.num_states = MAX_STATES}, "<Frequency> (U)", false, my_format},
        {TEXTFIELD_TOGGLE, (ToggleState){.txt_state = new_TextField(txt_max_size_1, height, width, start_y, start_x)}, "Token-> (L)", true},
        {TEXTFIELD_TOGGLE, (ToggleState){.txt_state = new_TextField(txt_max_size_2, height, width, start_y, start_x)}, "Name-> (U)", false},
    };
    int num_toggles = sizeof(toggles) / sizeof(toggles[0]);
    ToggleMenu toggle_menu = {0};

#ifndef S4C_RAYLIB_EXTENSION
    if (argc > 2) {
        toggle_menu = new_ToggleMenu_with_mouse(toggles, num_toggles, &default_ToggleMenu_mousehandler__);
    } else {
        toggle_menu = new_ToggleMenu(toggles, num_toggles);
    }
#else
    toggle_menu = new_ToggleMenu(toggles, num_toggles);
#endif // S4C_RAYLIB_EXTENSION

#ifndef S4C_RAYLIB_EXTENSION
    toggle_menu.statewin_height = LINES;
    toggle_menu.statewin_width = COLS/2;
    toggle_menu.statewin_start_x = COLS/2;
#else
    toggle_menu.statewin_height = 50;
    toggle_menu.statewin_width = 50;
    toggle_menu.statewin_start_x = 50;
#endif // S4C_RAYLIB_EXTENSION
    toggle_menu.statewin_start_y = 0;
    toggle_menu.statewin_boxed = true;
    toggle_menu.statewin_label = sidewin_label;
    toggle_menu.key_up = 'j';
    toggle_menu.key_down = 'k';

#ifndef S4C_RAYLIB_EXTENSION
    handle_ToggleMenu(toggle_menu);
#else
    while (!WindowShouldClose()) {
        // Update
        update_ToggleMenu(toggle_menu);
        BeginDrawing();
        // Draw
        ClearBackground(WHITE);
        draw_ToggleMenu(toggle_menu);
        EndDrawing();
    }
#endif // S4C_RAYLIB_EXTENSION

#ifndef S4C_RAYLIB_EXTENSION
    endwin(); // End ncurses
#else
    CloseWindow();
#endif // S4C_RAYLIB_EXTENSION
    free_ToggleMenu(toggle_menu);
    return 0;
}

int main(int argc, char** argv)
{
    if (argc > 1) {
        return togglemenu_main(argc, argv);
    } else {
        return textfield_main();
    }
}
#else
int main(int argc, char** argv)
{
    printf("TODO: build this.\n");
    return 0;
}
#endif // S4C_GUI_H_
