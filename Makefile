CC = gcc
CPP = g++
STANDART = -std=c++17
CFLAGS_C = -Wall -Wextra -Werror -std=c11
CFLAGS_CPP = -Wall -Wextra -Werror $(STANDART)
LDFLAGS = -lncurses
GTEST = -lgtest
GCOV = -fprofile-arcs -ftest-coverage
SF = -fsanitize=leak,address
DIST_DIR := archive

SNAKE_SRC =  ./brick_game/snake/controller/snake_controller.cpp ./brick_game/snake/model/snake_model.cpp
SNAKE_VIEW = ./brick_game/snake/snake_game.cpp ./gui/cli/snake_interface.cpp
SNAKE_GAME = $(SNAKE_SRC) $(SNAKE_VIEW)
TETRIS_SRC = ./brick_game/tetris/tetris_game.c ./brick_game/tetris/fsm/fsm.c ./gui/cli/tetris_interface.c
MAIN_SRC = ./brick_game/BrickGame_cli.cpp
TEST_SRC = ./tests/*.cpp

OBJ_TETRIS = $(TETRIS_SRC:.c=.o)
OBJ_SNAKE = $(SNAKE_GAME:.cpp=.o)
OBJ_MAIN = $(MAIN_SRC:.cpp=.o)

all: clean install

install: clean cli desktop
	rm -rf libtetris.a libsnake.a

cli: libtetris.a libsnake.a BrickGame_cli
	mkdir build
	mv BrickGame_cli build/

desktop:
	rm -rf desk
	mkdir desk
	cd desk && qmake ../gui/desktop
	cd desk && make
	mkdir -p build
	mv desk/BrickGame_Desktop build
	rm -rf desk

lib:
	sudo apt install libncursesw5-dev
	sudo apt install qt5-dev

BrickGame_cli: $(OBJ_MAIN) libtetris.a libsnake.a
	$(CPP) $(CFLAGS_CPP) $(OBJ_MAIN) -L. -ltetris -lsnake $(LDFLAGS) -o BrickGame_cli
	rm -rf $(OBJ_MAIN)

libsnake.a: $(OBJ_SNAKE)
	ar rc libsnake.a $(OBJ_SNAKE)
	ranlib libsnake.a
	rm -rf $(OBJ_SNAKE)

libtetris.a: $(OBJ_TETRIS)
	ar rc libtetris.a $(OBJ_TETRIS)
	ranlib libtetris.a
	rm -rf $(OBJ_TETRIS)

cli_run:
	./build/BrickGame_cli

desktop_run:
	./build/BrickGame_Desktop

dvi:
	@xdg-open dvi/Report.md
.PHONY: dvi

dist: clean_dist
	@cd ../ && mkdir -p ${DIST_DIR}
	@cd ../ && cp -rf src/brick_game ${DIST_DIR}/brick_game
	@cd ../ && cp -rf src/gui ${DIST_DIR}/gui
	@cd ../ && cp -rf src/Makefile ${DIST_DIR}/
	@cd ../ && tar -czvf archive.tar.gz ${DIST_DIR}
	@cd ../ && rm -rf ${DIST_DIR}

dist_unpack:
	@cd ../ && tar -xzvf archive.tar

test: clean
	$(CPP) $(CFLAGS_CPP) $(TEST_SRC) $(SNAKE_SRC) $(GTEST) -o tests/snake_tests
	./tests/snake_tests

gcov : clean
	$(CPP) -g $(CFLAGS_CPP) $(TEST_SRC) $(SNAKE_SRC) $(GTEST) $(GCOV) -lm -o tests/snake_tests
	./tests/snake_tests
	mkdir ./tests/gcov_report
	gcovr -r . --html --html-details -o ./tests/gcov_report/index.html
	gcovr -r . --txt -o ./tests/coverage_report.txt
	rm tests/*.gcda tests/*.gcno

	@xdg-open ./tests/gcov_report/index.html

gcov_clean:
	rm -rf tests/gcov_report/ tests/snake_tests tests/coverage_report.txt

clean:
	rm -rf *.o *.a build brick_game/*.o
	rm -rf $(OBJ_TETRIS) $(OBJ_SNAKE) $(OBJ_MAIN)
	rm -rf desk
	rm -rf tests/gcov_report/ tests/snake_tests tests/coverage_report.txt

uninstall:
	rm -rf build

clean_dist:
	@cd ../ && rm -rf archive
	@cd ../ && rm -rf archive.tar.gz