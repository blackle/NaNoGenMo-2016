#include <cstdlib>
#include <sstream>
#include "CellState.h"
#include "GameBoard.h"

int main(int argc, char* argv[]) {
  int w = 3*6;
  int h = 2*6;
  GameBoard g(w,h);
  

  std::cout << g;


  return 0;
}