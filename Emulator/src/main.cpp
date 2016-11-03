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
  int turnNum = 0;

  while (!g.isOver()) {
    turnNum++;
    std::cout << "Turn #" << turnNum << ": ";
    std::cout << ((g.currentPlayer() == PLAYER_BLACK) ? "It is my turn.\n" : "It is white's turn.\n");
    int dieA = 0;
    int dieB = 0;
    g.rollDice(dieA, dieB);
    std::cout << ((g.currentPlayer() == PLAYER_BLACK) ? "I rolled" : "White rolled") << " " << dieA+1 << " and " << dieB+1 << ".\n";

    PlayerName currentPlayer = g.currentPlayer();
    MoveList& moves = g.moves();

    if (moves.count() > 0) {
      Move m;

      int bestIndex = 0;
      int bestValue = 0;
      for (int k = 0; k < moves.count(); k++) {
        Move thisMove = moves(k);
        int thisValue = 0;
        if (currentPlayer == PLAYER_BLACK) {
          thisValue = thisMove.borderBlack*4 + thisMove.borderWhite*19;
        } else {
          thisValue = 0;//thisMove.borderBlack*2 + thisMove.borderWhite*1;
        }
        if (bestValue < thisValue) {
          bestValue = thisValue;
          bestIndex = k;
        }
      }

      if (bestValue == 0) {
        std::uniform_int_distribution<int> rng(0, moves.count()-1);
        m = moves(rng(RD));
      } else {
        m = moves(bestIndex);
      }
      std::cout << g;
      if (currentPlayer == PLAYER_BLACK) {
        std::cout << "I will place my rock in spot " << m.i+1 << ", " << m.j+1 << ". ";
        if (bestValue == 0) {
          std::cout << "This is because I picked randomly.\n";
        } else {
          if (m.borderBlack*4 < m.borderWhite*19) {
            std::cout << "This is because it would sabotage white, and prevent them from creating a territory of size " << m.borderWhite+1 << ".\n";
          } else {
            std::cout << "This is because it would give me a territory of size " << m.borderBlack+1 << ".\n";
          }
        }
      } else {
        std::cout << "White placed their rock in spot " << m.i+1 << ", " << m.j+1 << ".\n";
      }
      g.takeTurn(m,currentPlayer);
      std::cout << g;
    } else {
      std::cout << "No available spaces, have to roll again.\n";
    }
  }
  std::cout << ((g.winningPlayer() == PLAYER_BLACK) ? "I won " : "White won ") << "after " << turnNum << " turns.\n";
  return g.winningPlayer();
}

int main(int argc, char* argv[]) {
  int blackWins = 0;
  int whiteWins = 0;
  for (int k = 0; k < 1; k++) {
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
  // std::cout << "black wins: " << blackWins << "\n";
  // std::cout << "white wins: " << whiteWins << "\n";
  
  // std::cout << "black win %: " << (100.0*blackWins)/(1.0*blackWins+whiteWins) << "\n";

  return 0;
}