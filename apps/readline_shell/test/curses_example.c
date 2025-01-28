#include <ncurses.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

const char *choices[] = {
    "Option 1",
    "Option 2",
    "Option 3",
    "Exit"
};
int n_choices = ARRAY_SIZE(choices);

void print_menu(WINDOW *menu_win, int highlight);

int main() {
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    // Initialize ncurses
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);  // Hide the cursor

    int height = 10, width = 30, starty = 4, startx = 10;
    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE); // Enable arrow keys

    mvprintw(0, 0, "Use arrow keys to navigate. Press Enter to select.");
    refresh();
    print_menu(menu_win, highlight);

    while (1) {
        c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }
        print_menu(menu_win, highlight);
        if (choice) {
            if (choice == n_choices) { // Exit option
                break;
            } else {
                mvprintw(22, 0, "You chose option %d: %s", choice, choices[choice - 1]);
                clrtoeol();
            }
            refresh();
            choice = 0;
        }
    }

    endwin(); // End ncurses mode
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight) {
    int x = 2, y = 2;
    box(menu_win, 0, 0);
    for (int i = 0; i < n_choices; ++i) {
        if (highlight == i + 1) {
            wattron(menu_win, A_REVERSE); // Highlight selection
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}