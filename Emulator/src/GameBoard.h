#ifndef __GAME_BOARD__
#define __GAME_BOARD__
#include <iostream>
#include <sstream>
#include "CellState.h"

class GameBoard {
public:
  GameBoard();
  ~GameBoard();
  CellState& operator()(int i, int j);
  CellState operator()(int i, int j) const;
private:
  CellState* _states;
  CellState _fill;
};

std::ostream& operator <<(std::ostream& o, const GameBoard& board);

#endif
