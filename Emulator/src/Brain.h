#ifndef __BRAIN__
#define __BRAIN__
#include <string>
#include "MoveList.h"

class Brain {
public:
  Brain(std::string& name);
  ~Brain();
  int chooseMove(MoveList& m);
private:
  int (*_chooseMove)(MoveList& m);
  void* _handle;
  std::string _name;
};

#endif