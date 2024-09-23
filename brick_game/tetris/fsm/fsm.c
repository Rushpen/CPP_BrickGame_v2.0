#include "fsm.h"

#include "../tetris_game.h"

UserAction_t GetSignal(int UserInput) {
  UserAction_t rc = Action;

  if (UserInput == KEY_UP)
    rc = Up;
  else if (UserInput == KEY_DOWN)
    rc = Down;
  else if (UserInput == KEY_LEFT)
    rc = Left;
  else if (UserInput == KEY_RIGHT)
    rc = Right;
  else if (UserInput == EXIT_KEY)
    rc = Terminate;
  else if (UserInput == ENTER_KEY)
    rc = Enter;
  else if (UserInput == PAUSE_KEY)
    rc = Pause;

  return rc;
}

void ClearFigureArray(Shape *figure) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure->array[i][j] = ' ';
    }
  }
}

void CreateLineFigure(Shape *figure) {
  ClearFigureArray(figure);
  for (int j = 0; j < 4; j++) {
    figure->array[0][j] = '*';
  }
  figure->height = 1;
  figure->width = 4;
}

void CreateLFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][0] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateJFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][2] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateQuadrFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][0] = '*';
  figure->array[0][1] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->height = 2;
  figure->width = 2;
}

void CreateSFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][1] = '*';
  figure->array[0][2] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateTFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][1] = '*';
  figure->array[1][0] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void CreateZFigure(Shape *figure) {
  ClearFigureArray(figure);
  figure->array[0][0] = '*';
  figure->array[0][1] = '*';
  figure->array[1][1] = '*';
  figure->array[1][2] = '*';
  figure->height = 2;
  figure->width = 3;
}

void UpdateFigure(Shape *figure) {
  switch (rand() % 7) {
    case 0:
      CreateLineFigure(figure);
      break;
    case 1:
      CreateLFigure(figure);
      break;
    case 2:
      CreateJFigure(figure);
      break;
    case 3:
      CreateQuadrFigure(figure);
      break;
    case 4:
      CreateSFigure(figure);
      break;
    case 5:
      CreateTFigure(figure);
      break;
    case 6:
      CreateZFigure(figure);
      break;
  }
}

void CopyFigure(Shape *dst, Shape *src) {
  dst->height = src->height;
  dst->width = src->width;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dst->array[i][j] = src->array[i][j];
    }
  }
}

void ResetBgInfo(BrickgameInfo *BgInfo, PlayerPos *PlayerPos) {
  BgInfo->level = 1;
  BgInfo->score = 0;
  BgInfo->speed = 0;
  BgInfo->high_score = 0;

  for (int i = 0; i < FIELD_HEIGHT; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      BgInfo->cells[i][j] = ' ';
    }
  }

  PlayerPos->shape = NULL;
  PlayerPos->next_shape = NULL;
}

void ScoreAndLevel(int count, BrickgameInfo *BgInfo) {
  if (count == 1) {
    BgInfo->score += 100;
  } else if (count == 2) {
    BgInfo->score += 300;
  } else if (count == 3) {
    BgInfo->score += 700;
  } else if (count == 4) {
    BgInfo->score += 1500;
  }

  if (BgInfo->level < 11) {
    BgInfo->level = BgInfo->score / 600 + 1;
    if (BgInfo->level > 10) {
      BgInfo->level = 10;
    }
  }
  if (BgInfo->level % 2 == 0) {
    BgInfo->speed += 1;
  }
}

void CheckLines(BrickgameInfo *BgInfo) {
  int count = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    int sum = 0;
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (BgInfo->cells[i][j] == '*') sum++;
    }
    if (sum == 10) {
      count++;
      int l, k;
      for (k = i; k > 0; k--)
        for (l = 0; l < FIELD_WIDTH; l++)
          BgInfo->cells[k][l] = BgInfo->cells[k - 1][l];
      for (l = 0; l < FIELD_WIDTH; l++) BgInfo->cells[k][l] = ' ';
    }
  }
  ScoreAndLevel(count, BgInfo);
}

int GetHighScore() {
  FILE *fp = fopen("brick_game/score/TetrisScore.dat", "r");
  if (fp == NULL) {
    return 0;
  }
  int score = 0;
  if (fscanf(fp, "%d", &score) != 1) {
    score = 0;
  }
  fclose(fp);
  return score;
}

void PutHighScore(int score) {
  FILE *fp = fopen("brick_game/score/TetrisScore.dat", "w");
  if (fp == NULL) {
    return;
  }
  fprintf(fp, "%d", score);
  fclose(fp);
  return;
}

void ResetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo) {
  for (int i = 0; i < shape.height; ++i) {
    for (int j = 0; j < shape.width; ++j) {
      if (shape.array[i][j] == '*') {
        BgInfo->cells[object_pos->y + i][object_pos->x + j] = ' ';
      }
    }
  }
}

void SetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo) {
  for (int i = 0; i < shape.height; ++i) {
    for (int j = 0; j < shape.width; ++j) {
      if (shape.array[i][j] == '*') {
        BgInfo->cells[object_pos->y + i][object_pos->x + j] = '*';
      }
    }
  }
}

void ShiftTetrominoDown(PlayerPos *object_pos, Shape shape,
                        BrickgameInfo *BgInfo, Shape *newcurrent) {
  ResetElements(object_pos, shape, BgInfo);
  while (FigureDescByOneString(BgInfo, object_pos));
  CopyFigure(object_pos->shape, object_pos->next_shape);
  UpdateFigure(newcurrent);
  CopyFigure(object_pos->next_shape, newcurrent);
  object_pos->x = 4;
  object_pos->y = 0;
}

void MoveTetrominoRight(PlayerPos *object_pos, BrickgameInfo *BgInfo) {
  if (object_pos->x + object_pos->shape->width == 11) return;
  for (int j = 0; j < object_pos->shape->width; j++) {
    for (int i = 0; i < object_pos->shape->height; i++) {
      if ((object_pos->shape->array[i][j] == '*') &&
          (BgInfo->cells[i + object_pos->y][j + 1 + object_pos->x] == '*')) {
        return;
      }
    }
  }
  object_pos->x++;
}

void MoveTetrominoLeft(PlayerPos *object_pos, BrickgameInfo *BgInfo) {
  if (object_pos->x == 1) return;
  for (int j = 0; j < object_pos->shape->width; j++) {
    for (int i = 0; i < object_pos->shape->height; i++) {
      if ((object_pos->shape->array[i][j] == '*') &&
          (BgInfo->cells[i + object_pos->y][j - 1 + object_pos->x] == '*')) {
        return;
      }
    }
  }
  object_pos->x--;
}

void RotateClockwise(const Shape *src, Shape *dst) {
  for (int i = 0; i < src->height; i++) {
    for (int j = 0; j < src->width; j++) {
      dst->array[j][src->height - i - 1] = src->array[i][j];
    }
  }
}

void ShiftShapeDown(Shape *shape) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape->array[i][j] = shape->array[(i + 1) % 3][j];
    }
  }
  for (int j = 0; j < 3; j++) {
    shape->array[3][j] = ' ';
  }
}

void ShiftShapeRight(Shape *shape) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      shape->array[i][j] = shape->array[i][(j + 1) % 3];
    }
  }
  for (int i = 0; i < 3; i++) {
    shape->array[i][3] = ' ';
  }
}

void TryRotate(PlayerPos *object_pos) {
  Shape dst;
  dst.width = object_pos->shape->height;
  dst.height = object_pos->shape->width;

  if (object_pos->y + object_pos->shape->height > 19 ||
      object_pos->y + object_pos->shape->width > 19)
    return;

  if (dst.width != dst.height) {
    RotateClockwise(object_pos->shape, &dst);
    if (dst.width == 4 || dst.height == 4) {
      RotateClockwise(object_pos->shape, &dst);
    } else {
      if (dst.array[0][0] == ' ' && dst.array[0][1] == ' ' &&
          dst.array[0][2] == ' ') {
        ShiftShapeDown(&dst);
      }
      if (dst.array[0][0] == ' ' && dst.array[1][0] == ' ' &&
          dst.array[2][0] == ' ') {
        ShiftShapeRight(&dst);
      }
    }
    CopyFigure(object_pos->shape, &dst);
  }
}

void PutFigure2Field(BrickgameInfo *bGInfo, PlayerPos *object_pos) {
  for (int i = 0; i < object_pos->shape->height; i++) {
    for (int j = 0; j < object_pos->shape->width; j++) {
      if (object_pos->shape->array[i][j] == '*') {
        bGInfo->cells[object_pos->y + i][object_pos->x + j] = '*';
      }
    }
  }
}

int FigureDescByOneString(BrickgameInfo *bGInfo, PlayerPos *object_pos) {
  if (object_pos->y == 20 - object_pos->shape->height) {
    PutFigure2Field(bGInfo, object_pos);
    return 0;
  }
  for (int j = 0; j < object_pos->shape->width; j++) {
    for (int i = 0; i < object_pos->shape->height; i++) {
      if ((object_pos->shape->array[i][j] == '*') &&
          (bGInfo->cells[i + 1 + object_pos->y][j + object_pos->x] == '*')) {
        PutFigure2Field(bGInfo, object_pos);
        return 0;
      }
    }
  }
  object_pos->y++;
  return 1;
}

void Sigact(UserAction_t sig, TetrisState *state, PlayerPos *object_pos,
            bool *paused, BrickgameInfo *BgInfo, Shape *current,
            Shape *newcurrent) {
  bool gameover = false;
  switch (*state) {
    case PAUSE:
      HandlePauseState(sig, state, paused);
      break;
    case START:
      HandleStartState(sig, state, current, object_pos);
      break;
    case SPAWN:
      HandleSpawnState(newcurrent, state, object_pos);
      break;
    case MOVING:
      HandleMovingState(sig, BgInfo, object_pos, current, newcurrent, state,
                        paused);
      break;
    case GAMEOVER:
      HandleGameoverState(&gameover, sig, state, paused);
      break;
    default:
      break;
  }
}

void HandlePauseState(UserAction_t sig, TetrisState *state, bool *paused) {
  switch (sig) {
    case Pause:
      *state = MOVING;
      *paused = false;
      break;
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      *state = PAUSE;
      break;
  }
}

void HandleStartState(UserAction_t sig, TetrisState *state, Shape *current,
                      PlayerPos *object_pos) {
  UpdateFigure(current);
  object_pos->shape = current;
  switch (sig) {
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      *state = SPAWN;
      break;
  }
}

void HandleSpawnState(Shape *newcurrent, TetrisState *state,
                      PlayerPos *object_pos) {
  UpdateFigure(newcurrent);
  object_pos->next_shape = newcurrent;
  *state = MOVING;
}

void HandleMovingState(UserAction_t sig, BrickgameInfo *BgInfo,
                       PlayerPos *object_pos, Shape *current, Shape *newcurrent,
                       TetrisState *state, bool *paused) {
  HandleGameLogic(BgInfo, object_pos, current, newcurrent, state, paused);
  HandleUserInput(sig, BgInfo, object_pos, current, newcurrent, state, paused);
}

void HandleGameLogic(BrickgameInfo *BgInfo, PlayerPos *object_pos,
                     Shape *current, Shape *newcurrent, TetrisState *state,
                     bool *paused) {
  CheckLines(BgInfo);
  BgInfo->high_score = GetHighScore();
  ResetElements(object_pos, *current, BgInfo);
  if (FigureDescByOneString(BgInfo, object_pos) == 0) {
    CopyFigure(object_pos->shape, object_pos->next_shape);
    UpdateFigure(newcurrent);
    CopyFigure(object_pos->next_shape, newcurrent);
    object_pos->x = 4;
    object_pos->y = 0;
  }
  if (CheckEndGame(object_pos, BgInfo)) {
    *state = GAMEOVER;
    *paused = true;
  }
  SetElements(object_pos, *current, BgInfo);
  if (BgInfo->score > BgInfo->high_score) PutHighScore(BgInfo->score);
}

void HandleUserInput(int sig, BrickgameInfo *BgInfo, PlayerPos *object_pos,
                     Shape *current, Shape *newcurrent, TetrisState *state,
                     bool *paused) {
  switch (sig) {
    case Up:
      ResetElements(object_pos, *current, BgInfo);
      TryRotate(object_pos);
      SetElements(object_pos, *current, BgInfo);
      break;
    case Down:
      ShiftTetrominoDown(object_pos, *current, BgInfo, newcurrent);
      break;
    case Right:
      ResetElements(object_pos, *current, BgInfo);
      MoveTetrominoRight(object_pos, BgInfo);
      SetElements(object_pos, *current, BgInfo);
      break;
    case Left:
      ResetElements(object_pos, *current, BgInfo);
      MoveTetrominoLeft(object_pos, BgInfo);
      SetElements(object_pos, *current, BgInfo);
      break;
    case Pause:
      *state = PAUSE;
      *paused = true;
      break;
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      break;
  }
}

void HandleGameoverState(bool *gameover, UserAction_t sig, TetrisState *state,
                         bool *paused) {
  *gameover = true;
  switch (sig) {
    case Enter:
      *state = START;
      *gameover = false;
      *paused = false;
      break;
    case Terminate:
      *state = EXIT_STATE;
      break;
    default:
      *state = GAMEOVER;
      break;
  }
}

int CheckEndGame(PlayerPos *object_pos, BrickgameInfo *bGInfo) {
  int endGame = 0;
  for (int i = 0; i < object_pos->shape->height; i++) {
    for (int j = 0; j < object_pos->shape->width; j++) {
      if (object_pos->shape->array[i][j] == '*' &&
          bGInfo->cells[object_pos->y + i][object_pos->x + j] == '*') {
        endGame = 1;
      }
    }
  }
  return endGame;
}

void FillBoardWithSpaces(BrickgameInfo *BgInfo) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      BgInfo->cells[i][j] = ' ';
    }
  }
}