#include <ncurses.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "tetris/tetris_game.h"
#ifdef __cplusplus
}
#endif

#include "snake/snake_game.h"

void DisplayMenu(WINDOW *menu_win, int highlight);
