#include <cstdlib>
#include <sstream>
#include <cstring>
#include "CellState.h"
#include "GameBoard.h"

GameBoard::GameBoard(int w, int h) {
  _w = w;
  _h = h;
  int totalcells = w*h;
  size_t cellStateSize = sizeof(CellState);
  _states = (CellState*)malloc(cellStateSize*totalcells);
  std::memset(_states, CELL_EMPTY, cellStateSize*totalcells);
}

GameBoard::~GameBoard() {
  free(_states);
}

int GameBoard::width() const {
  return _w;
}

int GameBoard::height() const {
  return _h;
}

CellState GameBoard::operator()(int i, int j) const {
  if (i < 0 or i >= _w) {
    return CELL_OOB;
  }
  if (j < 0 or j >= _h) {
    return CELL_OOB;
  }
  return _states[i*_h+j];
}

CellState& GameBoard::operator()(int i, int j) {
  _fill = CELL_OOB;
  if (i < 0 or i >= _w) {
    return _fill;
  }
  if (j < 0 or j >= _h) {
    return _fill;
  }
  return _states[i*_h+j];
}

std::ostream& operator <<(std::ostream& o, const GameBoard& board) {
  for (int j = -1; j < board.height()+1; j++) {
    for (int i = -1; i < board.width()+1; i++) {
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
