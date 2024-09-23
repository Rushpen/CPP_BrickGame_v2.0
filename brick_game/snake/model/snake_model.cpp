#include "snake_model.h"

namespace s21 {

Position::Position() = default;
Position::Position(int x, int y) : x(x), y(y) {}

Position::Position(const Position& other) : x(other.x), y(other.y) {}

Position& Position::operator=(const Position& other) {
  if (this != &other) {
    x = other.x;
    y = other.y;
  }
  return *this;
}

bool Position::operator!=(const Position& other) const {
  return x != other.x || y != other.y;
}

bool Position::operator==(const Position& other) const {
  return x == other.x && y == other.y;
}

Position SnakeGame::SpawnApple() {
  Position ApplePos = {};
  bool validPosition = false;
  srand(time(0));
  while (!validPosition) {
    int randomX = rand() % (FIELD_WIDTH - 2) + 1;
    int randomY = rand() % (FIELD_HEIGHT - 2) + 1;
    ApplePos = Position(randomX, randomY);

    validPosition = true;
    for (const auto& pos : SnakePos) {
      if (ApplePos.x == pos.x && ApplePos.y == pos.y) {
        validPosition = false;
        break;
      }
    }
  }
  return ApplePos;
}

SnakeGame::SnakeGame(BrickgameInfo& Board) {
  State = START;
  CurrentDirection = DownDirection;
  NextDirection = DownDirection;
  Board.score = 0;
  Board.high_score = 0;
  Board.level = 1;
  Board.speed = MOVE_SPEED;
  ApplePosition = SpawnApple();
}

SnakeGame::~SnakeGame() = default;

void SnakeGame::InitSnake() {
  SnakePos.clear();
  SnakePos.push_back(Position(FIELD_WIDTH / 2 + 2, FIELD_HEIGHT / 2));
  SnakePos.push_back(Position(FIELD_WIDTH / 2 + 2, FIELD_HEIGHT / 2 - 1));
  SnakePos.push_back(Position(FIELD_WIDTH / 2 + 2, FIELD_HEIGHT / 2 - 2));
  SnakePos.push_back(Position(FIELD_WIDTH / 2 + 2, FIELD_HEIGHT / 2 - 3));
}

void SnakeGame::PrintSnake(BrickgameInfo& Board) {
  for (const auto& pos : SnakePos) {
    Board.cells[pos.y][pos.x] = 'o';
  }
  Board.cells[SnakePos.front().y][SnakePos.front().x] = 'O';
}

void SnakeGame::FillBoardWithSpaces(BrickgameInfo& Board) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      Board.cells[i][j] = ' ';
    }
  }
}

void SnakeGame::Reset(BrickgameInfo& Board) {
  Board.score = 0;
  Board.level = 1;
  Board.speed = MOVE_SPEED;

  State = START;
  CurrentDirection = DownDirection;
  NextDirection = DownDirection;

  FillBoardWithSpaces(Board);

  ApplePosition = SpawnApple();
  PrintApple(Board, ApplePosition);

  InitSnake();
  PrintSnake(Board);
}

void SnakeGame::PrintApple(BrickgameInfo& Board, Position& ApplePos) {
  Board.cells[ApplePos.y][ApplePos.x] = '#';
}

void SnakeGame::HandleAction(BrickgameInfo& Board) {
  switch (State) {
    case START:
      InitSnake();
      PrintSnake(Board);
      State = MOVING;
      break;
    case MOVING:
      SnakeMoving(Board);
      break;
    case PAUSE:
      break;
    case GAMEOVER:
      break;
    case EXIT_STATE:
      break;
    case WIN_STATE:
      break;
    default:
      break;
  }
}

Position SnakeGame::GetNewHeadPosition() {
  Position NewHead = SnakePos.front();
  switch (NextDirection) {
    case UpDirection:
      NewHead.y -= 1;
      break;
    case DownDirection:
      NewHead.y += 1;
      break;
    case RightDirection:
      NewHead.x += 1;
      break;
    case LeftDirection:
      NewHead.x -= 1;
      break;
    default:
      break;
  }
  return NewHead;
}

bool SnakeGame::CheckCollisions(const Position& NewHead) {
  bool result = false;
  if (NewHead.x <= 0 || NewHead.x >= FIELD_WIDTH ||
      NewHead.y >= FIELD_HEIGHT - 1 || NewHead.y <= 0) {
    result = true;
  }
  for (const auto& Pos : SnakePos) {
    if (NewHead.x == Pos.x && NewHead.y == Pos.y) {
      result = true;
    }
  }
  return result;
}

void SnakeGame::SnakeMoving(BrickgameInfo& Board) {
  Board.high_score = GetHighScore();
  const Position& Tail = SnakePos.back();
  Board.cells[Tail.y][Tail.x] = ' ';

  Position NewHead = GetNewHeadPosition();

  if (CheckCollisions(NewHead)) {
    State = GAMEOVER;
    return;
  }
  SnakeInsert(NewHead, Board);
}

void SnakeGame::SnakeInsert(Position& NewHead, BrickgameInfo& Board) {
  SnakePos.insert(SnakePos.begin(), NewHead);
  CurrentDirection = NextDirection;

  if (NewHead.x == ApplePosition.x && NewHead.y == ApplePosition.y) {
    Board.score += 1;
    CheckScoreAndLevel(Board);
    ApplePosition = SpawnApple();
    Board.cells[ApplePosition.y][ApplePosition.x] = '#';
  } else {
    SnakePos.pop_back();
  }
  PrintSnake(Board);
}

void SnakeGame::CheckScoreAndLevel(BrickgameInfo& Board) {
  if (Board.score == 200) {
    State = WIN_STATE;
    return;
  }

  if (Board.score > Board.high_score) {
    SetHighScore(Board.score);
  }
  if (Board.score >= 5) {
    if (Board.score < 51) {
      Board.level = 1 + Board.score / 5;
      Board.speed = 1200 - (Board.level * 100);
    }
  }
}

int SnakeGame::GetHighScore() {
  FILE* fp = fopen("brick_game/score/SnakeScore.dat", "r");
  if (fp == NULL) {
    return 0;
  }
  int HighScore = 0;
  if (fscanf(fp, "%d", &HighScore) != 1) {
    HighScore = 0;
  }
  fclose(fp);
  return HighScore;
}

void SnakeGame::SetHighScore(int HighScore) {
  FILE* fp = fopen("brick_game/score/SnakeScore.dat", "w");
  if (fp == NULL) {
    return;
  }
  fprintf(fp, "%d", HighScore);
  fclose(fp);
  return;
}

}  // namespace s21