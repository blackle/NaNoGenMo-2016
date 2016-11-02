#include <cstdlib>
#include <sstream>
#include "GameState.h"

int main(int argc, char* argv[]) {
  int w = 6*3;
  int h = 6*2;
  GameState g(w,h);
  g.rollDice();

  std::cout << g;

  return 0;
}