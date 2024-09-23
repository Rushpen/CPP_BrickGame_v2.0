#include "snake_controller.h"

namespace s21 {
SnakeController::SnakeController(SnakeGame *model) : model{model} {};
SnakeController::~SnakeController(){};

UserAction_t SnakeController::GetSignal(int UserInput) {
  UserAction_t rc = Action;
  switch (UserInput) {
    case KEY_UP:
      rc = Up;
      break;
    case KEY_DOWN:
      rc = Down;
      break;
    case KEY_LEFT:
      rc = Left;
      break;
    case KEY_RIGHT:
      rc = Right;
      break;
    case EXIT_KEY:
      rc = Terminate;
      break;
    case PAUSE_KEY:
      rc = Pause;
      break;
    default:
      break;
  }
  return rc;
}

void SnakeController::SwitchState(UserAction_t Key) {
  switch (Key) {
    case Up:
      model->State = MOVING;
      if (model->CurrentDirection != DownDirection)
        model->NextDirection = UpDirection;
      break;
    case Down:
      model->State = MOVING;
      if (model->CurrentDirection != UpDirection)
        model->NextDirection = DownDirection;
      break;
    case Left:
      model->State = MOVING;
      if (model->CurrentDirection != RightDirection)
        model->NextDirection = LeftDirection;
      break;
    case Right:
      model->State = MOVING;
      if (model->CurrentDirection != LeftDirection)
        model->NextDirection = RightDirection;
      break;
    case Terminate:
      model->State = EXIT_STATE;
      break;
    case Start:
      model->State = START;
      break;
    case Pause:
      model->State = PAUSE;
      break;
    default:
      break;
  }
}

void SnakeController::Sigact(UserAction_t sig, BrickgameInfo &Board) {
  SwitchState(sig);
  model->HandleAction(Board);
}

}  // namespace s21