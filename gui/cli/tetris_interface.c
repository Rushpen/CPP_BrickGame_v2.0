#include "../../brick_game/common/common.h"
#include "../../brick_game/tetris/tetris_game.h"

void PrintRectangle(BrickgameInfo *BgInfo) {
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

  for (int i = 1; i < FIELD_HEIGHT - 2; i++) {
    for (int j = 1; j < FIELD_WIDTH; j++) {
      char cell = BgInfo->cells[i][j];
      if (cell == '*') {
        attron(COLOR_PAIR(1));
      }
      mvprintw(i + 3, j * 2 + 1, "%c", BgInfo->cells[i][j]);
      mvprintw(i + 3, j * 2 + 2, " ");
      attroff(COLOR_PAIR(1));
    }
  }
}

void PrintField(BrickgameInfo *BgInfo) {
  mvprintw(1, FIELD_WIDTH - 3, "  TETRIS  ");
  PrintRectangle(BgInfo);
}

void PrintNextFigure(PlayerPos *object_pos) {
  printw("NEXT FIGURE:");
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      mvaddch(i + 13, j * 2 + 30, ' ');
      mvaddch(i + 13, j * 2 + 1 + 30, ' ');
      if (object_pos->next_shape != NULL &&
          object_pos->next_shape->array[i][j] == '*') {
        mvaddch(i + 13, j * 2 + 30, ACS_CKBOARD);
        mvaddch(i + 13, j * 2 + 1 + 30, ACS_CKBOARD);
      }
    }
  }
}

void PrintInfo(BrickgameInfo Info, bool paused, PlayerPos *object_pos) {
  mvprintw(4, FIELD_WIDTH * 2 + 3, "LEVEL: %d", Info.level);
  mvprintw(7, FIELD_WIDTH * 2 + 3, "SCORE: %d", Info.score);
  mvprintw(10, FIELD_WIDTH * 2 + 3, "RECORD SCORE: %d", Info.high_score);
  move(13, FIELD_WIDTH * 2 + 3);

  PrintNextFigure(object_pos);

  mvprintw(17, FIELD_WIDTH * 2 + 3, "Press 'Esc' to exit:");
  if (paused) {
    mvprintw(1, FIELD_WIDTH - 3, "  PAUSED  ");
  } else {
    mvprintw(1, FIELD_WIDTH - 3, "  TETRIS  ");
  }
}

void PrintGameoverText(BrickgameInfo BgInfo) {
  mvprintw(9, 7, "             ");
  mvprintw(10, 7, " Game Over ");
  mvprintw(11, 7, "your score:");
  mvprintw(12, 7, "     %d ", BgInfo.score);
  mvprintw(13, 7, "             ");
  mvprintw(14, 7, "Press Any key");
  mvprintw(15, 7, "  to Exit");
  mvprintw(16, 7, "             ");
}

void PrintOverlay(BrickgameInfo BgInfo, bool paused, PlayerPos *object_pos) {
  refresh();
  PrintField(&BgInfo);
  PrintInfo(BgInfo, paused, object_pos);
}
