#include <cstdlib>
#include <sstream>
#include <cstring>
#include "MoveList.h"

MoveList::MoveList(int size)
  : _size(size)
  , _count(0)
{
  size_t moveSize = size*sizeof(Move);
  _moves = (Move*)malloc(moveSize);
}

MoveList::~MoveList() {
  free(_moves);
}

int MoveList::count() const {
  return _count;
}

void MoveList::clear() {
  _count = 0;
}

void MoveList::addMove(Move& m) {
  if (_count == _size) {
    return;
  }
  _moves[_count] = m;
  _count++;
}


Move MoveList::operator()(int n) const {
  return _moves[n];
}

std::ostream& operator <<(std::ostream& o, const MoveList& moves) {
  o << "Moves:\n";
  for (int i = 0; i < moves.count(); i++) {
    Move m = moves(i);
    o << " (" << m.i << ", " << m.j << ")\n";
  }
}
