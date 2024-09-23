#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_FSM_H
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_FSM_H

#include "../../common/common.h"
#include "../tetris_game.h"

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  REACH,
  PAUSE,
  JOINING,
  GAMEOVER,
  EXIT_STATE
} TetrisState;

// Creating figures
void ClearFigureArray(Shape *figure);
void CreateLineFigure(Shape *figure);
void CreateLFigure(Shape *figure);
void CreateJFigure(Shape *figure);
void CreateQuadrFigure(Shape *figure);
void CreateSFigure(Shape *figure);
void CreateTFigure(Shape *figure);
void CreateZFigure(Shape *figure);

// Operations with figures
void UpdateFigure(Shape *figure);
void CopyFigure(Shape *dst, Shape *src);
void ResetBgInfo(BrickgameInfo *bGInfo, PlayerPos *PlayerPos);

void ResetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo);
void SetElements(PlayerPos *object_pos, Shape shape, BrickgameInfo *BgInfo);

void ShiftTetrominoDown(PlayerPos *object_pos, Shape shape,
                        BrickgameInfo *BgInfo, Shape *newcurrent);
void MoveTetrominoRight(PlayerPos *object_pos, BrickgameInfo *BgInfo);
void MoveTetrominoLeft(PlayerPos *object_pos, BrickgameInfo *BgInfo);

// Functions for rotate
void RotateClockwise(const Shape *src, Shape *dst);
void ShiftShapeDown(Shape *shape);
void ShiftShapeRight(Shape *shape);
void TryRotate(PlayerPos *object_pos);

void PutFigure2Field(BrickgameInfo *bGInfo, PlayerPos *pos);
int FigureDescByOneString(BrickgameInfo *bGInfo, PlayerPos *pos);

// Handles
void HandleGameLogic(BrickgameInfo *BgInfo, PlayerPos *object_pos,
                     Shape *current, Shape *newcurrent, TetrisState *state,
                     bool *paused);

void HandleUserInput(int sig, BrickgameInfo *BgInfo, PlayerPos *object_pos,
                     Shape *current, Shape *newcurrent, TetrisState *state,
                     bool *paused);

// Handles States
void HandlePauseState(UserAction_t sig, TetrisState *state, bool *paused);

void HandleStartState(UserAction_t sig, TetrisState *state, Shape *current,
                      PlayerPos *object_pos);

void HandleSpawnState(Shape *newcurrent, TetrisState *state,
                      PlayerPos *object_pos);

void HandleMovingState(UserAction_t sig, BrickgameInfo *BgInfo,
                       PlayerPos *object_pos, Shape *current, Shape *newcurrent,
                       TetrisState *state, bool *paused);

void HandleGameoverState(bool *gameover, UserAction_t sig, TetrisState *state,
                         bool *paused);

void ScoreAndLevel(int count, BrickgameInfo *BgInfo);
void CheckLines(BrickgameInfo *BgInfo);
int CheckEndGame(PlayerPos *pos, BrickgameInfo *bGInfo);
void FillBoardWithSpaces(BrickgameInfo *BgInfo);

// Processing control
UserAction_t GetSignal(int user_input);

void Sigact(UserAction_t sig, TetrisState *state, PlayerPos *object_pos,
            bool *paused, BrickgameInfo *BgInfo, Shape *current,
            Shape *newcurrent);

#endif