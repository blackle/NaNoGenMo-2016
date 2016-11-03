#ifndef __GAME_STATE__
#define __GAME_STATE__
#include <iostream>
#include <sstream>
#include "PlayerName.h"
#include "TerritoryTracker.h"
#include "GameBoard.h"
#include "MoveList.h"

class GameState {
public:
  GameState(int w, int h);
  ~GameState();
  int width() const;
  int height() const;
  void rollDice(int& dieA, int& dieB);
  bool takeTurn(Move m, PlayerName name);
  bool isOver();
  PlayerName currentPlayer() const;
  PlayerName opponentPlayer() const;
  PlayerName winningPlayer() const;
  CellState playerToCell(PlayerName player) const;
  MoveList& moves();
private:
  friend std::ostream& operator <<(std::ostream& o, const GameState& state);
  void fillCanGo(int m, int n, int x, int y);
  void setCanGo(int x, int y);
  void cleanUpPostTurn();
  void nextPlayer();

  int _w;
  int _h;

  bool _secondRoll;
  int _dieA;
  int _dieB;
  int _spacesFilled;
  GameBoard _g;
  TerritoryTracker _tBlack;
  TerritoryTracker _tWhite;
  MoveList _moves;
  PlayerName _current;
};

#endif
