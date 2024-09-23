#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tetrisWidget(nullptr), snakeWidget(nullptr) {
  QWidget *centralWidget = new QWidget(this);

  buttonTetris = new QPushButton("Tetris", centralWidget);
  buttonSnake = new QPushButton("Snake", centralWidget);

  QFont boldFont;
  boldFont.setBold(true);
  buttonTetris->setFont(boldFont);
  buttonSnake->setFont(boldFont);

  connect(buttonTetris, &QPushButton::clicked, this,
          &MainWindow::OpenTetrisWidget);
  connect(buttonSnake, &QPushButton::clicked, this,
          &MainWindow::OpenSnakeWidget);

  QVBoxLayout *tetrisLayout = new QVBoxLayout;
  tetrisLayout->addWidget(buttonTetris);

  QVBoxLayout *snakeLayout = new QVBoxLayout;
  snakeLayout->addWidget(buttonSnake);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addLayout(tetrisLayout);
  mainLayout->addLayout(snakeLayout);

  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  setFixedSize(400, 200);
  setStyleSheet("QMainWindow {background: 'lightGray';}");
  setWindowTitle("BrickGame v2.0");
}

MainWindow::~MainWindow() {
  delete tetrisWidget;
  delete snakeWidget;
}

void MainWindow::OpenTetrisWidget() {
  if (!tetrisWidget) {
    tetrisWidget = new TetrisWidget(this);
  }
  tetrisWidget->show();
}

void MainWindow::OpenSnakeWidget() {
  if (!snakeWidget) {
    snakeWidget = new SnakeWidget(this);
  }
  snakeWidget->show();
}