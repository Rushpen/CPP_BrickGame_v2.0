#include "TetrisWidget.h"

TetrisWidget::TetrisWidget(QWidget *parent)
    : QMainWindow(parent),
      state(START),
      timer(new QTimer(this)),
      paused(false) {
  ResetBgInfo(&Bginfo, &figure);
  setWindowTitle("TETRIS");
  setStyleSheet("QMainWindow {background: 'lightGray';}");
  setFixedSize(600, 600);

  gameField = new QWidget(this);
  gameField->setMinimumSize(300, 600);

  labelLevel = new QLabel("Level : 0");
  labelScore = new QLabel("Score : 0");
  labelHighScore = new QLabel("Record Score: 0");
  labelSpeed = new QLabel("Current Speed: 0");
  labelNextShape = new QLabel("Next figure: ");

  int labelHeight = 20;
  labelLevel->setFixedHeight(labelHeight);
  labelScore->setFixedHeight(labelHeight);
  labelHighScore->setFixedHeight(labelHeight);
  labelSpeed->setFixedHeight(labelHeight);
  labelNextShape->setFixedHeight(labelHeight);

  QVBoxLayout *labelsLayout = new QVBoxLayout();
  labelsLayout->addWidget(labelLevel);
  labelsLayout->addWidget(labelScore);
  labelsLayout->addWidget(labelHighScore);
  labelsLayout->addWidget(labelSpeed);
  labelsLayout->addWidget(labelNextShape);

  QHBoxLayout *mainLayout = new QHBoxLayout();
  mainLayout->addWidget(gameField);
  mainLayout->addLayout(labelsLayout);

  QWidget *centralWidget = new QWidget(this);
  centralWidget->setLayout(mainLayout);
  setCentralWidget(centralWidget);

  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &TetrisWidget::UpdateGame);
  timer->start(MOVE_SPEED / 2);
}

TetrisWidget::~TetrisWidget() {
  delete timer;
}

void TetrisWidget::UpdateLabels(const BrickgameInfo &info) {
  labelLevel->setText(QString("Level: %1").arg(info.level));
  labelScore->setText(QString("Score: %1").arg(info.score));
  labelHighScore->setText(QString("Record Score: %1").arg(info.high_score));
  labelSpeed->setText(QString("Current Speed: %1").arg(info.speed));
}

void TetrisWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);

  for (int i = 2; i < FIELD_HEIGHT; ++i) {
    for (int j = 1; j < FIELD_WIDTH; ++j) {
      if (Bginfo.cells[i - 2][j] == '*') {
        painter.setBrush(Qt::blue);
      } else {
        painter.setBrush(Qt::white);
      }
      painter.drawRect(j * 25 + 20, i * 25 + 20, 25, 25);
    }
  }

  if (figure.next_shape != nullptr) {
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 4; ++j) {
        if (figure.next_shape->array[i][j] == '*') {
          painter.setBrush(Qt::blue);
          painter.drawRect(j * 25 + 320, i * 25 + 530, 25, 25);
        }
      }
    }
  }
}

void TetrisWidget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Down) {
    signal = Down;
  } else if (event->key() == Qt::Key_Up) {
    signal = Up;
  } else if (event->key() == Qt::Key_Left) {
    signal = Left;
  } else if (event->key() == Qt::Key_Right) {
    signal = Right;
  } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    signal = Start;
  } else if (event->key() == Qt::Key_Escape) {
    signal = Terminate;
  } else if (event->key() == 'p' || event->key() == 'P') {
    signal = Pause;
  } else if (event->key() == 'z' || event->key() == 'Z') {
    signal = Action;
  }
  Sigact(signal, &state, &figure, &paused, &Bginfo, &currentShape, &nextShape);
  update();
}

int TetrisWidget::ShowMessageBox(int score) {
  QMessageBox msgBox;
  msgBox.setWindowTitle("Game Over!");
  msgBox.setText(
      QString("Your Score: %1 \nDo you want to restart game?").arg(score));
  msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
  msgBox.setDefaultButton(QMessageBox::No);
  msgBox.resize(100, 50);

  int result = msgBox.exec();
  return result;
}

void TetrisWidget::UpdateGame() {
  Sigact(Enter, &state, &figure, &paused, &Bginfo, &currentShape, &nextShape);
  if (state == EXIT_STATE) {
    ResetBgInfo(&Bginfo, &figure);
    close();
  }
  if (state == GAMEOVER) {
    timer->stop();
    int reply = ShowMessageBox(Bginfo.score);
    if (reply == QMessageBox::Yes) {
      timer->start();
      FillBoardWithSpaces(&Bginfo);
      state = START;
    } else {
      close();
    }
    ResetBgInfo(&Bginfo, &figure);
  }
  UpdateLabels(Bginfo);
  update();
}
