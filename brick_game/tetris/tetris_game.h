#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_H

#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "../common/common.h"

typedef struct {
  char array[4][4];
  int width, height, col;
} Shape;

typedef struct {
  int x;
  int y;
  Shape *shape;
  Shape *next_shape;
} PlayerPos;

void FillBoardWithSpaces(BrickgameInfo *BgInfo);
void PrintRectangle(BrickgameInfo *BgInfo);
void PrintField(BrickgameInfo *BgInfo);
void PrintInfo(BrickgameInfo Info, bool paused, PlayerPos *object_pos);
void PrintOverlay(BrickgameInfo BgInfo, bool paused, PlayerPos *object_pos);
void PrintGameoverText(BrickgameInfo BgInfo);

void TetrisLoop();
void TetrisInitializeColors();
void TetrisGameLoop();

#endif