#ifndef __GAME_BOARD__
#define __GAME_BOARD__
#include <iostream>
#include <sstream>
#include "CellState.h"

class GameBoard {
public:
  GameBoard(int w, int h);
  ~GameBoard();
  int width() const;
  int height() const;
  CellState& operator()(int i, int j);
  CellState operator()(int i, int j) const;
private:
  int _w;
  int _h;
  CellState* _states;
  CellState _fill;
};

std::ostream& operator <<(std::ostream& o, const GameBoard& board);

#endif
