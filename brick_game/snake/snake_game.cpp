#include "snake_game.h"

void SnakeGameLoop() {
  srand(time(0));
  initscr();
  SnakeInitializeColors();
  noecho();
  keypad(stdscr, TRUE);
  cbreak();
  curs_set(0);
  SnakeLoop();
  endwin();
}

void SnakeLoop() {
  s21::Ncurses SnakeNcurses;
  BrickgameInfo Board;
  s21::SnakeGame SGame(Board);
  s21::SnakeController Controller(&SGame);

  bool exit = false;
  UserAction_t signal;

  SGame.FillBoardWithSpaces(Board);

  SGame.ApplePosition = SGame.SpawnApple();
  SGame.PrintApple(Board, SGame.ApplePosition);

  while (!exit) {
    timeout(Board.speed);
    SnakeNcurses.PrintOverlay(Board);

    signal = Controller.GetSignal(getch());
    Controller.Sigact(signal, Board);

    if (SGame.State == s21::EXIT_STATE) {
      exit = true;
    } else if (SGame.State == s21::GAMEOVER) {
      timeout(-1);
      SnakeNcurses.PrintGameoverText(Board);
      SGame.FillBoardWithSpaces(Board);
      if (getch() != ERR) exit = true;
    } else if (SGame.State == s21::WIN_STATE) {
      timeout(-1);
      SGame.FillBoardWithSpaces(Board);
      SnakeNcurses.PrintWinText(Board);
      if (getch() != ERR) exit = true;
    } else if (SGame.State == s21::PAUSE) {
      SnakeNcurses.PrintPauseText();
      timeout(-1);
      if (getch() == PAUSE_KEY) SGame.State = s21::MOVING;
    }
  }
  refresh();
}

void SnakeInitializeColors() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_GREEN);
  init_pair(4, COLOR_RED, COLOR_RED);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(6, COLOR_BLACK, COLOR_GREEN);
}