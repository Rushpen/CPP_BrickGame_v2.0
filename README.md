# BrickGame Snake
Summary: In this project implemented the Snake game in the C++ programming language in the object-oriented programming paradigm.

# Contents

- [BrickGame Snake](#brickgame-snake)
  - [Contents](#contents)
  - [Introduction](#introduction)
- [Chapter I](#chapter-i)
  - [General Information](#general-information)
    - [Snake](#snake)
    - [MVC Pattern](#mvc-pattern)
- [Chapter II](#chapter-ii)
  - [Project Requirments](#project-requirements)
    - [Part 1. Main task](#part-1-main-task)
    - [Part 2. Bonus. Scoring and game record](#part-2-bonus-scoring-and-game-record)
    - [Part 3. Bonus. Level mechanics](#part-3-bonus-level-mechanics)
- [Chapter III](#chapter-iii)
  - [Overview](#overview)
## Introduction

The project consists of two separate components to implement the Snake game: a library responsible for implementing the game logic and a desktop GUI.

The developed library must also be connected to the console interface of BrickGame v1.0. The console interface must fully support the new game.

The Tetris game developed in BrickGame v1.0 must be connected to the desktop interface developed in this project. It must fully support the game.

## Chapter I 
# General information

### Snake

The player controls a snake that moves forward continuously. The player changes the direction of the snake by using the arrows. The goal of the game is to collect "apples" that appear on the playing field. The player must avoid hitting the walls of the playing field. After "eating" the next "apple", the length of the snake increases by one. The player wins when the snake reaches the maximum size (200 "pixels"). If the snake hits a boundary of the playing field, the player loses.

### MVC Pattern

The Model-View-Controller (MVC) pattern divides an application into three parts: the model, which handles business logic, the view, which is the user interface, and the controller, which updates the model based on user input.

MVC was introduced by Trygve Reenskaug in 1978 and later implemented in Smalltalk-80. Its goal is to separate the business logic from the user interface, making it easier to update or replace the view without changing the logic.

The model manages key data and operations, while the controller acts as a bridge between the view and the model, ensuring efficient interaction. The controller is "thin," meaning it mostly passes requests from the view to the model, allowing the model to remain encapsulated from the user interface. This separation makes it easier to adapt the code for different algorithms or platforms, requiring fewer changes in the interface.

In the Snake game, the class library managing the game mechanics functions as the model, providing the logic necessary for gameplay.

The view contains all the code associated with the program interface. There should be no business logic in the code of a perfect interface. It is just a form for user interaction.

![MVC-Process](dvi/media/MVC-Process.png)

## Chapter II 
## Project Requirements

### Part 1. Main task

Implement BrickGame v2.0:

- The program must be developed in C++ language of C++17 standard.
- The program must consist of two parts: a library that implements the logic of the snake game and a desktop interface.
- A finite state machine must be used to formalize the logic of the game.
 The library must conform to the specification given in the first part of BrickGame (you can find it in materials/library-specification.md).
- The program library code must be in the `src/brick_game/snake` folder.
- The program interface code must be in the `src/gui/desktop` folder.
- Follow Google Style when writing code.
- Classes must be implemented within the `s21` namespace.
- The library that implements the game logic must be covered by unit tests. 
- Pay special attention to checking FMS states and transitions. Use the GTest library for testing. The coverage of the library with tests must be at least 80 percent.
- The program must be built using a Makefile with the standard set of targets for GNU programs: all, install, uninstall, clean, dvi, dist, tests. The installation directory can be arbitrary.
- The implementation must have a GUI based on one of the GUI libraries with an API for C++17:
  - Qt
  - GTK+
- The program must be implemented using the MVC pattern. Also 
  - There must be no business logic code in the view code;
  - There must be no interface code in the model, presenter, and view model;
  - Controllers must be thin.
- Copy the game logic library folder from the BrickGame v1.0 project.
- The desktop interface must support the game from the BrickGame v1.0 project.
- Copy the console interface folder from the BrickGame v1.0 project.
The console interface must support the snake.
- The following mechanics must be present in the Snake game:
  - The snake must move on its own, one block ahead, when the game timer runs out.
  - When the snake hits an "apple", its length increases by one.
  - When the length of the snake reaches 200 units, the game ends and the player wins.
  - If a snake hits a field boundary or itself, the game ends with the player losing.
  - The user can change the direction of the snake's movement using the arrows, and the snake can only turn left and right relative to the current direction of movement.
  - The user can speed up the snake's movement by pressing the action key.
- The initial length of the snake is four "pixels".
- The playing field is 10 "pixels" wide and 20 "pixels" high.
- Prepare a diagram showing all states and transitions between them for the implemented FMS for project submission.

### Part 2. Bonus. Scoring and game record

Add the following mechanics to the game:

- scoring;
- storing maximum points.

This information must be passed and displayed by the user interface in the sidebar. The maximum score must be stored in a file or an embedded DBMS and saved between program runs.

The maximum score must be changed during the game if the user exceeds the current maximum score.

Points are scored as follows: eating another "apple" adds one point.

### Part 3. Bonus. Level Mechanics

Add level mechanics to the game. Each time a player gains 5 points, the level increases by 1. Increasing the level increases the snake's speed. The maximum number of levels is 10.

## Chapter III
## Overview

## Installation

1) do `git clone` repository.
2) navigame to `src/` directory.
3) run `make install` or just `make` to install project.
4) run `make run_cli` to start play in cli.
5) run `make run_desktop` to start play in desktop.

![make install](src/dvi/media/install_cli_run.gif)

## Show Game

## Tetris CLI Gameplay

![Tetris CLI Gameplay](src/dvi/media/tetris_cli.gif)

## Snake CLI Gameplay

![Snake CLI Gameplay](src/dvi/media/snake_cli.gif)

## Tetris Desktop Gameplay

![Tetris Desktop Gameplay](src/dvi/media/tetris_desktop.gif)

## Snake Desktop Gameplay

![Snake Desktop Gameplay](src/dvi/media/snake_desktop.gif)


## Finite State Machine (FSM) Diagram Tetris

![My diagram](src/dvi/media/fsm_tetris.png)

## Finite State Machine (FSM) Diagram Snake

![My diagram](src/dvi/media/fsm_snake.png)