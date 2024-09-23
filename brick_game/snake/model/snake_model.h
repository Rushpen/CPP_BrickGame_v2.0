#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_MODEL_H
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_MODEL_SNAKE_MODEL_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "../../common/common.h"

namespace s21 {

typedef enum {
  START = 0,
  MOVING,
  SPAWN,
  SHIFTING,
  PAUSE,
  GAMEOVER,
  EXIT_STATE,
  WIN_STATE
} SnakeState;

typedef enum {
  UpDirection,
  DownDirection,
  RightDirection,
  LeftDirection
} Direction;

class Position {
 public:
  int x;
  int y;
  Position();
  Position(int x, int y);
  Position(const Position &other);
  Position &operator=(const Position &other);
  bool operator!=(const Position &other) const;
  bool operator==(const Position &other) const;
};

class SnakeGame {
 public:
  BrickgameInfo Board;
  SnakeState State;
  Direction CurrentDirection;
  Direction NextDirection;
  Position ApplePosition;
  std::vector<Position> SnakePos;

  SnakeGame(BrickgameInfo &Board);
  ~SnakeGame();

  void Reset(BrickgameInfo &Board);
  void InitSnake();
  void PrintSnake(BrickgameInfo &Board);

  void FillBoardWithSpaces(BrickgameInfo &Board);
  void PrintApple(BrickgameInfo &Board, Position &ApplePos);

  void HandleAction(BrickgameInfo &Board);

  Position GetNewHeadPosition();
  bool CheckCollisions(const Position &NewHead);
  void SnakeInsert(Position &NewHead, BrickgameInfo &Board);
  void SnakeMoving(BrickgameInfo &Board);

  Position SpawnApple();
  void CheckScoreAndLevel(BrickgameInfo &Board);

  int GetHighScore();
  void SetHighScore(int Score);
};

}  // namespace s21

#endif