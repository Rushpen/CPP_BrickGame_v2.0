#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_CONTROLLER_SNAKE_CONTROLLER_H
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_CONTROLLER_SNAKE_CONTROLLER_H

#include <ncurses.h>

#include "../../common/common.h"
#include "../model/snake_model.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController(SnakeGame *model);
  ~SnakeController();

  UserAction_t GetSignal(int UserInput);
  void SwitchState(UserAction_t Key);
  void Sigact(UserAction_t sig, BrickgameInfo &Board);

 private:
  SnakeGame *model;
};

}  // namespace s21

#endif