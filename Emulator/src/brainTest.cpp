#include <cstdlib>
#include <sstream>
#include <string>
#include "Brain.h"

int main(int argc, char* argv[]) {
  std::string name("brainExample");
  Brain b(name);
  MoveList m;
  std::cout << b.chooseMove(m) << "\n";
}