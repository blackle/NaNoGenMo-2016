#ifndef __GAME_STATE__
#define __GAME_STATE__
#include <iostream>
#include <sstream>
#include "PlayerName.h"
#include "TerritoryTracker.h"
#include "GameBoard.h"

class GameState {
public:
  GameState(int w, int h);
  ~GameState();
  int width() const;
  int height() const;
  void rollDice();
  bool takeTurn(int i, int j, PlayerName name);
  PlayerName currentPlayer() const;
private:
  friend std::ostream& operator <<(std::ostream& o, const GameState& state);
  void fillCanGo(int m, int n, int x, int y);
  void setCanGo(int x, int y);
  void cleanUpPostTurn();

  int _w;
  int _h;

  int _dieA;
  int _dieB;
  GameBoard _g;
  TerritoryTracker _tBlack;
  TerritoryTracker _tWhite;
  PlayerName _current;
};

#endif
