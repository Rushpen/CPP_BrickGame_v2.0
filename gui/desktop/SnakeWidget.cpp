#include "SnakeWidget.h"

SnakeWidget::SnakeWidget(QWidget *parent)
    : QMainWindow(parent),
      Bginfo{},
      SGame{Bginfo},
      timer(new QTimer(this)),
      Controller(&SGame) {
  setWindowTitle("SNAKE");
  setStyleSheet("QMainWindow {background: 'lightGray';}");
  setFixedSize(600, 600);

  gameField = new QWidget(this);
  gameField->setMinimumSize(300, 600);

  labelLevel = new QLabel("Level :");
  labelScore = new QLabel("Score :");
  labelHighScore = new QLabel("Record Score:");
  labelSpeed = new QLabel("Current Speed:");

  labelPaused = new QLabel("Game Paused");
  labelPaused->setStyleSheet("QLabel { color: red; font-size: 20px; }");
  labelPaused->setGeometry(150, 250, 300, 50);
  labelPaused->setVisible(false);  // Изначально скрыта

  int labelHeight = 20;
  labelLevel->setFixedHeight(labelHeight);
  labelScore->setFixedHeight(labelHeight);
  labelHighScore->setFixedHeight(labelHeight);
  labelSpeed->setFixedHeight(labelHeight);

  QVBoxLayout *labelsLayout = new QVBoxLayout();
  labelsLayout->addWidget(labelLevel);
  labelsLayout->addWidget(labelScore);
  labelsLayout->addWidget(labelHighScore);
  labelsLayout->addWidget(labelSpeed);
  labelsLayout->addWidget(labelPaused);

  QHBoxLayout *mainLayout = new QHBoxLayout();
  mainLayout->addWidget(gameField);
  mainLayout->addLayout(labelsLayout);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &SnakeWidget::UpdateGame);
  timer->start(MOVE_SPEED);
}

SnakeWidget::~SnakeWidget() {
  delete timer;
}

void SnakeWidget::UpdateLabels(const BrickgameInfo &info) {
  labelLevel->setText(QString("Level: %1").arg(info.level));
  labelScore->setText(QString("Score: %1").arg(info.score));
  labelHighScore->setText(QString("Record Score: %1").arg(info.high_score));
  labelSpeed->setText(QString("Current Speed: %1").arg(1 + (MOVE_SPEED - info.speed) / 100));
}

void SnakeWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  for (int i = 2; i < FIELD_HEIGHT; ++i) {
    for (int j = 1; j < FIELD_WIDTH; ++j) {
      if (Bginfo.cells[i - 1][j] == 'O') {
        painter.setBrush(Qt::yellow);
      } else if (Bginfo.cells[i - 1][j] == 'o') {
        painter.setBrush(Qt::green);
      } else if (Bginfo.cells[i - 1][j] == '#') {
        painter.setBrush(Qt::red);
      } else {
        painter.setBrush(Qt::white);
      }
      painter.drawRect(j * 25 + 20, i * 25 + 20, 25, 25);
    }
  }
  SGame.PrintApple(Bginfo, SGame.ApplePosition);
}

void SnakeWidget::keyPressEvent(QKeyEvent *event) {
  signal = Start;
  if (event->key() == Qt::Key_Down) {
    signal = Down;
  } else if (event->key() == Qt::Key_Up) {
    signal = Up;
  } else if (event->key() == Qt::Key_Left) {
    signal = Left;
  } else if (event->key() == Qt::Key_Right) {
    signal = Right;
  } else if (event->key() == Qt::Key_Escape) {
    signal = Terminate;
  } else if (event->key() == 'p' || event->key() == 'P') {
    signal = Pause;
  } else if (event->key() == 'z' || event->key() == 'Z') {
    signal = Action;
  }
  Controller.Sigact(signal, Bginfo);
  update();
}

int SnakeWidget::GameOverMessageBox(int score) {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Game Over!");
  msgBox.setText(
      QString("Your Score: %1 \nDo you want to restart game?").arg(score));
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.resize(100, 50);

  int result = msgBox.exec();
  return result;
}

int SnakeWidget::WinnerMessageBox() {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Congrats!");
  msgBox.setText("Your Score: 200 \n");
  msgBox.setStandardButtons(QMessageBox::Ok);
  msgBox.resize(100, 50);

  int result = msgBox.exec();
  return result;
}

void SnakeWidget::ResetBoard(BrickgameInfo &Bginfo) {
  timer->stop();
  SGame.FillBoardWithSpaces(Bginfo);
  SGame.Reset(Bginfo);
  SGame.State = s21::START;
}

void SnakeWidget::UpdateGame() {
  timer->start(Bginfo.speed);
  Controller.Sigact(signal, Bginfo);

  if (SGame.State == s21::EXIT_STATE) {
    ResetBoard(Bginfo);
    close();
  } else if (SGame.State == s21::GAMEOVER) {
    int score = Bginfo.score;
    ResetBoard(Bginfo);
    signal = Down;
    if (GameOverMessageBox(score) == QMessageBox::Yes) {
      timer->start(Bginfo.speed);
    } else {
      close();
    }
  } else if (SGame.State == s21::PAUSE) {
    labelPaused->setVisible(true);
    timer->stop();
    if (signal == Pause) {
      labelPaused->setVisible(false);
      timer->start(Bginfo.speed);
    }
  } else if (SGame.State == s21::WIN_STATE) {
    ResetBoard(Bginfo);
    if(WinnerMessageBox() == QMessageBox::Ok)
      close();
  }
  UpdateLabels(Bginfo);

  update();
}