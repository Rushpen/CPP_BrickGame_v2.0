#include <vector>

#include "../brick_game/snake/controller/snake_controller.h"
#include "gtest/gtest.h"
#include "tests.h"

namespace s21 {

class SnakeGameTest : public ::testing::Test {
 protected:
  BrickgameInfo Bginfo;
  SnakeGame game{Bginfo};
  SnakeController controller{&game};
  UserAction_t action;

  void SetUp() override { game.Reset(Bginfo); }
};
}  // namespace s21
