#include <cstdlib>
#include <sstream>
#include <random>
#include "GameState.h"

static std::random_device RD_SOURCE;
static std::minstd_rand RD(RD_SOURCE());
// static std::random_device RD;

PlayerName playGame() {
  int w = 6*3;
  int h = 6*2;
  GameState g(w,h);

  while (!g.isOver()) {
    g.rollDice();

    PlayerName currentPlayer = g.currentPlayer();
    MoveList& moves = g.moves();

    if (moves.count() > 0) {
      Move m;
      if (currentPlayer == PLAYER_BLACK) {
        std::uniform_int_distribution<int> rng(0, moves.count()-1);
        m = moves(rng(RD));
      } else {
        std::uniform_int_distribution<int> rng(0, moves.count()-1);
        m = moves(rng(RD));
      }
      g.takeTurn(m,currentPlayer);
    }
  }
  // std::cout << g;
  return g.winningPlayer();
}

int main(int argc, char* argv[]) {
  int blackWins = 0;
  int whiteWins = 0;
  for (int k = 0; k < 200000; k++) {
    PlayerName winner = playGame();
    switch (winner) {
      case PLAYER_WHITE:
        whiteWins++; break;
      case PLAYER_BLACK:
        blackWins++; break;
      default:
        break;
    }
  }
  std::cout << "black wins: " << blackWins << "\n";
  std::cout << "white wins: " << whiteWins << "\n";

  return 0;
}