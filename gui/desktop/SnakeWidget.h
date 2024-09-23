#ifndef SNAKE_WIDGET_H
#define SNAKE_WIDGET_H

#include <QDebug>
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
#include "../../brick_game/snake/controller/snake_controller.h"
#include "../../brick_game/snake/model/snake_model.h"

class SnakeWidget : public QMainWindow {
  Q_OBJECT

 public:
  explicit SnakeWidget(QWidget *parent = nullptr);
  ~SnakeWidget();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void UpdateLabels(const BrickgameInfo &info);
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void ResetBoard(BrickgameInfo &Bginfo);
  void UpdateGame();
  int GameOverMessageBox(int score);
  int WinnerMessageBox();

 private:
  QLabel *labelLevel;
  QLabel *labelScore;
  QLabel *labelHighScore;
  QLabel *labelSpeed;
  QLabel *labelPaused;
  QWidget *gameField;
  BrickgameInfo Bginfo;
  s21::SnakeGame SGame;
  QTimer *timer;
  s21::SnakeController Controller;
  UserAction_t signal;
};

#endif