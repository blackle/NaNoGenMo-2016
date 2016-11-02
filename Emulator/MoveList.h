#ifndef __MOVE_LIST__
#define __MOVE_LIST__
#include <iostream>
#include <sstream>
#include "Move.h"

class MoveList {
public:
  MoveList(int size);
  ~MoveList();
  void addMove(Move m);
  void clear();
  Move operator()(int n) const;
private:
  int _size;
  Move* _moves;
};

std::ostream& operator <<(std::ostream& o, const MoveList& moves);

#endif