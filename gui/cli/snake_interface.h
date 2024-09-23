#include <ncurses.h>

#include "../../brick_game/common/common.h"
#include "../../brick_game/snake/model/snake_model.h"

namespace s21 {

class Ncurses {
 public:
  Ncurses();
  ~Ncurses();

  void PrintRectangle(BrickgameInfo *BgInfo);
  void PrintField(BrickgameInfo *BgInfo);
  void PrintInfo(BrickgameInfo &Info);
  void PrintPauseText();

  void PrintGameoverText(BrickgameInfo &BgInfo);
  void PrintOverlay(BrickgameInfo &BgInfo);
  void PrintWinText(BrickgameInfo &Board);
};

}  // namespace s21