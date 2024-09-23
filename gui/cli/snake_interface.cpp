#include "snake_interface.h"

namespace s21 {

Ncurses::Ncurses() = default;

Ncurses::~Ncurses() {}

void Ncurses::PrintRectangle(BrickgameInfo *Board) {
  for (int i = 2; i <= FIELD_HEIGHT + 1; i++) {
    mvaddch(i, 2, ACS_VLINE);
    mvaddch(i, FIELD_WIDTH * 2 + 1, ACS_VLINE);
  }

  for (int i = 2; i <= FIELD_WIDTH * 2 + 1; i++) {
    mvaddch(2, i, ACS_HLINE);
    mvaddch(FIELD_HEIGHT + 1, i, ACS_HLINE);
  }

  mvaddch(2, 2, ACS_ULCORNER);
  mvaddch(2, FIELD_WIDTH * 2 + 1, ACS_URCORNER);
  mvaddch(FIELD_HEIGHT + 1, 2, ACS_LLCORNER);
  mvaddch(FIELD_HEIGHT + 1, FIELD_WIDTH * 2 + 1, ACS_LRCORNER);

  for (int i = 1; i < FIELD_HEIGHT - 1; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      char cell = Board->cells[i][j];
      if (cell == 'O') {
        attron(COLOR_PAIR(5));
      } else if (cell == 'o') {
        attron(COLOR_PAIR(3));
      } else if (cell == '#') {
        attron(COLOR_PAIR(4));
      } else {
        attroff(COLOR_PAIR(5));
        attroff(COLOR_PAIR(3));
        attroff(COLOR_PAIR(4));
      }
      mvprintw(i + 2, j * 2 + 1, "%c", cell);
      mvprintw(i + 2, j * 2 + 2, " ");
      attroff(COLOR_PAIR(5));
      attroff(COLOR_PAIR(3));
      attroff(COLOR_PAIR(4));
    }
  }
  refresh();
}

void Ncurses::PrintField(BrickgameInfo *Board) {
  PrintRectangle(Board);
  refresh();
}

void Ncurses::PrintInfo(BrickgameInfo &Info) {
  attron(COLOR_PAIR(1));
  mvprintw(1, FIELD_WIDTH - 3, "  SNAKE ");
  attroff(COLOR_PAIR(1));
  attron(COLOR_PAIR(2));
  mvprintw(4, FIELD_WIDTH * 2 + 3, "LEVEL: %d", Info.level);
  mvprintw(7, FIELD_WIDTH * 2 + 3, "SCORE: %d", Info.score);
  mvprintw(10, FIELD_WIDTH * 2 + 3, "RECORD SCORE: %d", Info.high_score);
  mvprintw(13, FIELD_WIDTH * 2 + 3, "CURRENT SPEED: %d",
           1 + (MOVE_SPEED - Info.speed) / 100);
  attroff(COLOR_PAIR(2));
  mvprintw(17, FIELD_WIDTH * 2 + 3, "Press 'Esc' to exit:");
  mvprintw(20, FIELD_WIDTH * 2 + 3, "Press 'p' to pause: ");
  mvprintw(1, FIELD_WIDTH - 3, "  SNAKE  ");
  refresh();
}

void Ncurses::PrintPauseText() {
  attron(COLOR_PAIR(6));
  mvprintw(10, FIELD_WIDTH - 6, "               ");
  mvprintw(11, FIELD_WIDTH - 6, "               ");
  mvprintw(12, FIELD_WIDTH - 6, "     PAUSED    ");
  mvprintw(13, FIELD_WIDTH - 6, "               ");
  mvprintw(14, FIELD_WIDTH - 6, "               ");
  attroff(COLOR_PAIR(6));
}

void Ncurses::PrintGameoverText(BrickgameInfo &Board) {
  attron(COLOR_PAIR(1));
  mvprintw(9, 7, "             ");
  mvprintw(10, 8, " Game Over ");
  mvprintw(11, 7, " your score: ");
  mvprintw(12, 8, "     %d    ", Board.score);
  mvprintw(13, 7, "             ");
  mvprintw(14, 5, "  Press Any key");
  mvprintw(15, 7, "   to exit ");
  mvprintw(16, 7, "             ");
  attroff(COLOR_PAIR(1));
}

void Ncurses::PrintOverlay(BrickgameInfo &Board) {
  PrintField(&Board);
  PrintInfo(Board);
  refresh();
}

void Ncurses::PrintWinText(BrickgameInfo &Board) {
  mvprintw(9, 7, "             ");
  mvprintw(10, 7, " Congrats! ");
  mvprintw(11, 7, "Your score:");
  mvprintw(12, 7, "     %d    ", Board.score);
  mvprintw(13, 7, "             ");
  mvprintw(14, 6, "Press Any key");
  mvprintw(15, 7, "  to exit'");
  mvprintw(16, 7, "             ");
  refresh();
}

}  // namespace s21