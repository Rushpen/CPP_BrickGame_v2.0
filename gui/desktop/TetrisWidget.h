#ifndef TETRIS_WIDGET_H
#define TETRIS_WIDGET_H

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

#include "../../brick_game/common/common.h"

extern "C" {
#include "../../brick_game/tetris/fsm/fsm.h"
}

class TetrisWidget : public QMainWindow {
  Q_OBJECT

 public:
  explicit TetrisWidget(QWidget *parent = nullptr);
  ~TetrisWidget();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void UpdateLabels(const BrickgameInfo &info);
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void UpdateGame();
  int ShowMessageBox(int score);

 private:
  UserAction_t signal;
  TetrisState state;
  QTimer *timer;
  bool paused;
  PlayerPos figure = {4, 0, 0, 0};
  Shape currentShape = {};
  Shape nextShape = {};
  int fieldWidth = FIELD_WIDTH - 1;
  int fieldHeight = FIELD_HEIGHT - 2;
  QLabel *labelLevel;
  QLabel *labelScore;
  QLabel *labelHighScore;
  QLabel *labelSpeed;
  QLabel *labelNextShape;
  QWidget *gameField;
  BrickgameInfo Bginfo;
};

#endif