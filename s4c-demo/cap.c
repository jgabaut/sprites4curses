#include "../src/s4c.h"

int main(int argc, char** argv)
{
    printf("Using s4c v%s\n", string_s4c_version());

    setlocale(LC_ALL, "");
    initscr();
    clear();
    refresh();
    start_color();

    int curses_COLORS = COLORS;

    int res = s4c_check_term();
    switch (res) {
        case S4C_ERR_TERMCOLOR: {
            fprintf(stderr, "Terminal does not support color\n");
        }
        break;
        case S4C_ERR_TERMCHANGECOLOR: {
            fprintf(stderr, "Terminal does not support changing colors\n");
        }
        break;
        default: {
            fprintf(stderr, "Unknown result for s4c_check_term(): (%i)\n", res);
        }
        break;
    }

    mvwprintw(stdscr, 1, 1, "\x1b[38;2;120;200;255mcustom rgb\x1b[0m");
    printw("\x1b[38;2;255;0;0mRed text\x1b[0m");
    refresh();

    wgetch(stdscr);

    endwin();

    printf("curses COLORS: %i\n", curses_COLORS);

    return 0;
}
