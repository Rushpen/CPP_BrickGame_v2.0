#include "BrickGame_cli.h"

void DisplayMenu(WINDOW *menu_win, int highlight) {
  const char *choices[] = {"Tetris", "Snake", "Exit"};
  int n_choices = sizeof(choices) / sizeof(char *);
  int x = 3, y = 3;

  wbkgd(menu_win, COLOR_PAIR(1));
  box(menu_win, 0, 0);
  for (int i = 0; i < n_choices; ++i) {
    if (highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else {
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    }
    ++y;
  }
  wrefresh(menu_win);
}

int main() {
  initscr();
  clear();
  noecho();
  cbreak();
  curs_set(0);

  int highlight = 1;
  int choice = 0;
  int input;
  int startx = 0, starty = 0;
  int width = 20, height = 9;

  WINDOW *menu_win =
      newwin(height, width, (LINES - height) / 2, (COLS - width) / 2);
  keypad(menu_win, TRUE);
  DisplayMenu(menu_win, highlight);

  while (1) {
    input = wgetch(menu_win);
    switch (input) {
      case KEY_UP:
        if (highlight == 1)
          highlight = 3;
        else
          --highlight;
        break;
      case KEY_DOWN:
        if (highlight == 3)
          highlight = 1;
        else
          ++highlight;
        break;
      case 10:
        choice = highlight;
        break;
      default:
        break;
    }
    DisplayMenu(menu_win, highlight);
    if (choice != 0) break;
  }

  clear();
  refresh();
  delwin(menu_win);
  endwin();

  if (choice == 1) {
    initscr();
    TetrisGameLoop();
  } else if (choice == 2) {
    initscr();
    SnakeGameLoop();
  }

  endwin();
  return 0;
}