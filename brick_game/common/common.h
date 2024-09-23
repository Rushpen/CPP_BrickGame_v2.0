#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_H
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_COMMON_H

#define START_LEVEL 1
#define START_SCORE 0
#define FIELD_WIDTH 11
#define FIELD_HEIGHT 22
#define EXIT_KEY 27
#define ENTER_KEY '\n'
#define PAUSE_KEY 112
#define MOVE_SPEED 1200

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Enter
} UserAction_t;

typedef struct {
  char cells[FIELD_HEIGHT][FIELD_WIDTH];
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} BrickgameInfo;

#endif