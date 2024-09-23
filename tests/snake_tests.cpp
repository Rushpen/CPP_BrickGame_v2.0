#include "snake_tests.h"

namespace s21 {

TEST_F(SnakeGameTest, InitialState) {
  EXPECT_EQ(game.State, START);
  EXPECT_EQ(Bginfo.score, 0);
  EXPECT_EQ(Bginfo.level, 1);
  EXPECT_EQ(Bginfo.speed, MOVE_SPEED);
}

TEST_F(SnakeGameTest, SpawnApple) {
  Position apple = game.SpawnApple();
  EXPECT_GE(apple.x, 1);
  EXPECT_LT(apple.x, FIELD_WIDTH - 1);
  EXPECT_GE(apple.y, 1);
  EXPECT_LT(apple.y, FIELD_HEIGHT - 1);
}

TEST_F(SnakeGameTest, SnakeMoving) {
  Position initial_head = game.SnakePos.front();
  UserAction_t signal = Down;
  controller.SwitchState(signal);

  BrickgameInfo temp_Bginfo;
  game.SnakeMoving(temp_Bginfo);

  Position new_head = game.SnakePos.front();
  EXPECT_EQ(new_head.y, initial_head.y + 1);
}

TEST_F(SnakeGameTest, CheckCollisionWithWall) {
  game.SnakePos.clear();
  game.SnakePos.push_back(Position(0, 0));
  Position new_head = game.GetNewHeadPosition();
  EXPECT_TRUE(game.CheckCollisions(new_head));
}

TEST_F(SnakeGameTest, CheckCollisionWithWall1) {
  game.InitSnake();
  const Position head_position = {0, 0};
  game.SnakePos[0] = head_position;

  bool collided = game.CheckCollisions(head_position);

  EXPECT_TRUE(collided);
}

TEST_F(SnakeGameTest, GetWinState) {
  Bginfo.score = 199;
  Bginfo.score += 1;
  EXPECT_EQ(Bginfo.score, 200);

  game.CheckScoreAndLevel(Bginfo);

  EXPECT_EQ(game.State, s21::WIN_STATE);
}

TEST_F(SnakeGameTest, SnakeEatingApple) {
  game.InitSnake();

  Position head_position = game.SnakePos.front();
  Position apple_position = head_position;
  apple_position.y += 1;
  game.ApplePosition = apple_position;

  game.SnakeMoving(Bginfo);

  EXPECT_EQ(Bginfo.score, 1);
  EXPECT_NE(game.ApplePosition, apple_position);
}

TEST_F(SnakeGameTest, LevelAndSpeedIncrease) {
  Bginfo.score = 5;
  game.CheckScoreAndLevel(Bginfo);

  EXPECT_EQ(Bginfo.level, 2);
  EXPECT_LT(Bginfo.speed, MOVE_SPEED);
}

TEST_F(SnakeGameTest, LevelMaxAndSpeedMax) {
  Bginfo.score = 49;
  game.CheckScoreAndLevel(Bginfo);
  Bginfo.score += 1;
  EXPECT_EQ(Bginfo.score, 50);
  EXPECT_EQ(Bginfo.level, 10);
  EXPECT_EQ(Bginfo.speed, 200);
}

TEST_F(SnakeGameTest, SnakeCollisionWithSelf) {
  game.InitSnake();
  game.SnakePos[0] = game.SnakePos.back();

  bool collided = game.CheckCollisions(game.SnakePos.front());

  EXPECT_TRUE(collided);
}

TEST_F(SnakeGameTest, GamePause) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Pause);
  game.HandleAction(Bginfo);

  EXPECT_EQ(game.SnakePos.front(), initial_head_position);
}

TEST_F(SnakeGameTest, SnakeMovingLeft) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Left);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().x, initial_head_position.x - 1);
}

TEST_F(SnakeGameTest, SnakeMovingRight) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Right);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().x, initial_head_position.x + 1);
}

TEST_F(SnakeGameTest, SnakeMovingDown) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Down);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().y, initial_head_position.y + 1);
}

TEST_F(SnakeGameTest, SnakeMovingUp) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Right);
  game.SnakeMoving(Bginfo);
  controller.SwitchState(Up);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().y, initial_head_position.y - 1);
}

TEST_F(SnakeGameTest, SnakeNoMovingLeft) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Right);
  game.SnakeMoving(Bginfo);
  controller.SwitchState(Left);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().x, initial_head_position.x + 2);
}

TEST_F(SnakeGameTest, SnakeNoMovingRight) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Left);
  game.SnakeMoving(Bginfo);
  controller.SwitchState(Right);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().x, initial_head_position.x - 2);
}

TEST_F(SnakeGameTest, SnakeNoMovingDown) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();
  controller.SwitchState(Right);
  game.SnakeMoving(Bginfo);
  controller.SwitchState(Up);
  game.SnakeMoving(Bginfo);
  controller.SwitchState(Down);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().y, initial_head_position.y - 2);
}

TEST_F(SnakeGameTest, SnakeNoMovingUp) {
  game.InitSnake();
  Position initial_head_position = game.SnakePos.front();

  controller.SwitchState(Up);
  game.SnakeMoving(Bginfo);

  EXPECT_EQ(game.SnakePos.front().y, initial_head_position.y + 1);
}

TEST_F(SnakeGameTest, SnakeIsRenderedCorrectly) {
  game.InitSnake();

  game.FillBoardWithSpaces(Bginfo);
  game.PrintSnake(Bginfo);
  EXPECT_EQ(Bginfo.cells[game.SnakePos.front().y][game.SnakePos.front().x],
            'O');
  for (size_t i = 1; i < game.SnakePos.size(); ++i) {
    EXPECT_EQ(Bginfo.cells[game.SnakePos[i].y][game.SnakePos[i].x], 'o');
  }
}

TEST_F(SnakeGameTest, SnakeExitState) {
  game.InitSnake();
  controller.SwitchState(Terminate);

  EXPECT_EQ(game.State, s21::EXIT_STATE);
}

TEST_F(SnakeGameTest, SnakeStartState) {
  game.InitSnake();
  controller.SwitchState(Start);

  EXPECT_EQ(game.State, s21::START);
}

TEST_F(SnakeGameTest, SnakeGetSignal) {
  game.InitSnake();
  action = controller.GetSignal(KEY_UP);
  EXPECT_EQ(action, Up);

  action = controller.GetSignal(KEY_DOWN);
  EXPECT_EQ(action, Down);

  action = controller.GetSignal(KEY_LEFT);
  EXPECT_EQ(action, Left);

  action = controller.GetSignal(KEY_RIGHT);
  EXPECT_EQ(action, Right);

  action = controller.GetSignal(EXIT_KEY);
  EXPECT_EQ(action, Terminate);

  action = controller.GetSignal(PAUSE_KEY);
  EXPECT_EQ(action, Pause);

  action = controller.GetSignal(0);
  EXPECT_EQ(action, Action);
}

TEST_F(SnakeGameTest, SnakeSigact) {
  game.InitSnake();
  controller.Sigact(Terminate, Bginfo);
  EXPECT_EQ(game.State, EXIT_STATE);
}

TEST_F(SnakeGameTest, HandleActionStartState) {
  game.State = START;

  game.HandleAction(Bginfo);
  EXPECT_EQ(game.State, MOVING);
}

TEST_F(SnakeGameTest, HandleActionMovingState) {
  game.State = MOVING;
  game.HandleAction(Bginfo);
  EXPECT_EQ(game.State, MOVING);
}

TEST_F(SnakeGameTest, SnakeTriggersWinState) {
  game.InitSnake();
  game.SnakeMoving(Bginfo);
  Bginfo.score = 200;
  game.CheckScoreAndLevel(Bginfo);
  game.HandleAction(Bginfo);
  EXPECT_EQ(game.State, WIN_STATE);
}

}  // namespace s21