QT += widgets
SOURCES += main.cpp \
            mainwindow.cpp \
            SnakeWidget.cpp \
            TetrisWidget.cpp \
            ../../brick_game/tetris/fsm/fsm.c \
            ../../brick_game/snake/controller/snake_controller.cpp \
            ../../brick_game/snake/model/snake_model.cpp

HEADERS += mainwindow.h \
            SnakeWidget.h \
            TetrisWidget.h \
            ../../brick_game/tetris/fsm/fsm.h \
            ../../brick_game/snake/controller/snake_controller.h \
            ../../brick_game/snake/model/snake_model.h

QMAKE_CXXFLAGS += -lstdc++