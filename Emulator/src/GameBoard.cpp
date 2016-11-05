#include <cstdlib>
#include <sstream>
#include <cstring>
#include "RoyalClod.h"
#include "CellState.h"
#include "GameBoard.h"

GameBoard::GameBoard() {
  int totalcells = WIDTH*HEIGHT;
  size_t statesSize = sizeof(CellState)*totalcells;
  _states = (CellState*)malloc(statesSize);
  std::memset(_states, CELL_EMPTY, statesSize);
}

GameBoard::~GameBoard() {
  free(_states);
}

CellState GameBoard::operator()(int i, int j) const {
  if (i < 0 or i >= WIDTH) {
    return CELL_OOB;
  }
  if (j < 0 or j >= HEIGHT) {
    return CELL_OOB;
  }
  return _states[i*HEIGHT+j];
}

CellState& GameBoard::operator()(int i, int j) {
  _fill = CELL_OOB;
  if (i < 0 or i >= WIDTH) {
    return _fill;
  }
  if (j < 0 or j >= HEIGHT) {
    return _fill;
  }
  return _states[i*HEIGHT+j];
}

std::ostream& operator <<(std::ostream& o, const GameBoard& board) {
  for (int j = -1; j < HEIGHT+1; j++) {
    for (int i = -1; i < WIDTH+1; i++) {
      CellState cell = board(i,j);
      switch (cell) {
        case CELL_OOB:
          o << "\033[48;2;60;60;60m  \033[0m"; break;
        case CELL_EMPTY:
          o << "\033[48;2;128;128;128m  \033[0m"; break;
        case CELL_BLACK:
          o << "\033[48;2;0;0;0m  \033[0m"; break;
        case CELL_WHITE:
          o << "\033[48;2;255;255;255m  \033[0m"; break;
        case CELL_CANGO:
          o << "\033[48;2;255;0;0m  \033[0m"; break;
        default:
          o << "??"; break;
      }
    }
    std::cout << "\n";
  }
}
