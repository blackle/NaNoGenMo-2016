#include <cstdlib>
#include <sstream>
#include <random>
#include <thread>
#include <mutex>
#include "GameState.h"

static std::random_device RD_SOURCE;
static std::minstd_rand RD(RD_SOURCE());
// static std::random_device RD;

#define SAMPLE_SIZE 2000
#define THREADS 8

static std::mutex mtx;
static int blackSampleTotal = 0;
static int whiteSampleTotal = 0;

int evaluator(Move& m, int turns, GameState& g) {
  if (turns == -1) {
    return m.borderBlack*4 + m.borderWhite*18;
  } else {
    return (m.borderBlack+1)*5 + (m.borderWhite+1)*18;
  }
}

PlayerName playGame() {
  GameState g;
  int turnNum = 0;

  while (!g.isOver()) {
    turnNum++;
    int dieA = 0;
    int dieB = 0;
    g.rollDice(dieA, dieB);

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
          thisValue = evaluator(thisMove, turnNum, g);
        } else {
          // thisValue = 0;
          thisValue = thisMove.borderWhite*4 + thisMove.borderBlack*19;
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
      g.takeTurn(m,currentPlayer);
    }
  }
  return g.winningPlayer();
}

int collectStats() {
  int blackWins = 0;
  int whiteWins = 0;
  for (int k = 0; k < SAMPLE_SIZE; k++) {
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

  mtx.lock();
  blackSampleTotal += blackWins;
  whiteSampleTotal += whiteWins;
  mtx.unlock();
}

int main(int argc, char* argv[]) {
  std::thread threads[THREADS];

  for (int i=0; i<THREADS; ++i)
    threads[i] = std::thread(collectStats);

  for (auto& th : threads) th.join();

  std::cout << "black wins: " << blackSampleTotal << "\n";
  std::cout << "white wins: " << whiteSampleTotal << "\n";
  
  float winPercent = (100.0*blackSampleTotal)/(1.0*blackSampleTotal+whiteSampleTotal);
  std::cout << "black win %: " << winPercent << "\n";

  return 0;
}