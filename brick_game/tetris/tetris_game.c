#include "tetris_game.h"

#include "fsm/fsm.h"

void TetrisGameLoop() {
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  halfdelay(MOVE_SPEED / 300);
  TetrisInitializeColors();
  TetrisLoop();
  endwin();
}

void TetrisLoop() {
  int signal = 0;
  TetrisState state = START;
  bool break_flag = TRUE;
  PlayerPos figure = {4, 0, 0, 0};
  bool paused = false;
  BrickgameInfo board;
  ResetBgInfo(&board, &figure);
  FillBoardWithSpaces(&board);
  Shape current = {};
  Shape newcurrent = {};

  while (break_flag) {
    PrintOverlay(board, paused, &figure);
    if (state == EXIT_STATE) break_flag = FALSE;
    if (state == GAMEOVER) {
      FillBoardWithSpaces(&board);
      PrintGameoverText(board);
    }

    Sigact(GetSignal(signal), &state, &figure, &paused, &board, &current,
           &newcurrent);
    signal = getch();

    refresh();
  }
}

void TetrisInitializeColors() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_RED);
}