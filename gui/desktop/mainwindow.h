#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "SnakeWidget.h"
#include "TetrisWidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void OpenTetrisWidget();
  void OpenSnakeWidget();

 private:
  QLabel *labelTetris;
  QLabel *labelSnake;
  QPushButton *buttonTetris;
  QPushButton *buttonSnake;

  TetrisWidget *tetrisWidget;
  SnakeWidget *snakeWidget;
};

#endif  // MAINWINDOW_H