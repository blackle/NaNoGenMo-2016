#include <cstdlib>
#include <sstream>
#include <cstring>
#include "MoveList.h"

MoveList::MoveList(int size)
  : _size(size)
{
  size_t moveSize = size*sizeof(Move);
  _moves = (Move*)malloc(moveSize);
  std::memset(_moves, CELL_EMPTY, moveSize);
}
