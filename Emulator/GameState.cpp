#include <cstdlib>
#include <sstream>
#include <cstring>
#include <random>
#include "GameState.h"

static std::random_device RD;
static std::uniform_int_distribution<int> DICE(0, 5);

GameState::GameState(int w, int h)
  : _g(w,h)
  , _tBlack(w,h)
  , _tWhite(w,h)
  , _dieA(-1)
  , _dieB(-1)
  , _w(w)
  , _h(h)
  , _current(PLAYER_BLACK)
{
}

GameState::~GameState() {
}

int GameState::width() const {
  return _w;
}

int GameState::height() const {
  return _h;
}

void GameState::rollDice() {
  _dieA = DICE(RD);
  _dieB = DICE(RD);

  int subSquaresM = _w/6;
  int subSquaresN = _h/6;

  for (int m = 0; m < subSquaresM; m++) {
    for (int n = 0; n < subSquaresN; n++) {
      fillCanGo(m,n,_dieA,_dieB);
      fillCanGo(m,n,_dieB,_dieA);
    }
  }
}

void GameState::fillCanGo(int m, int n, int x, int y) {
  if (m%3 != 2 || n%2 != 1) {
    if (m%2) x = 5-x;
    if (n%2) y = 5-y;
  }

  int globX = m*6 + x;
  int globY = n*6 + y;

  CellState cell = _g(globX,globY);
  if (cell == CELL_EMPTY) {
    setCanGo(globX,globY);
    return;
  }

  if (cell == CELL_BLACK || cell == CELL_WHITE) {
    if (_g(globX-1,globY-1) == CELL_EMPTY) setCanGo(globX-1,globY-1);
    if (_g(globX-1,globY+0) == CELL_EMPTY) setCanGo(globX-1,globY+0);
    if (_g(globX-1,globY+1) == CELL_EMPTY) setCanGo(globX-1,globY+1);
    if (_g(globX+0,globY-1) == CELL_EMPTY) setCanGo(globX+0,globY-1);
    if (_g(globX+0,globY+1) == CELL_EMPTY) setCanGo(globX+0,globY+1);
    if (_g(globX+1,globY-1) == CELL_EMPTY) setCanGo(globX+1,globY-1);
    if (_g(globX+1,globY+0) == CELL_EMPTY) setCanGo(globX+1,globY+0);
    if (_g(globX+1,globY+1) == CELL_EMPTY) setCanGo(globX+1,globY+1);
  }
}

void GameState::setCanGo(int x, int y) {
  _g(x,y) = CELL_CANGO;
}

bool GameState::takeTurn(int i, int j, PlayerName name) {
  if (name != _current) {
    return false;
  }

  if (_dieA == -1 or _dieB == -1) {
    return false;
  }

  if (_g(i,j) != CELL_CANGO) {
    return false;
  }

  _g(i,j) = ((name == PLAYER_BLACK) ? CELL_BLACK : CELL_WHITE);
  _current = ((name == PLAYER_BLACK) ? PLAYER_WHITE : PLAYER_BLACK);
  if (name == PLAYER_BLACK) {
    _tBlack.placeAt(i,j);
  } else {
    _tWhite.placeAt(i,j);
  }

  cleanUpPostTurn();

  return true;
}

void GameState::cleanUpPostTurn() {
  _dieA = -1;
  _dieB = -1;
  for (int i = 0; i < _w; i++) {
    for (int j = 0; j < _h; j++) {
      if (_g(i,j) == CELL_CANGO) _g(i,j) = CELL_EMPTY;
    }
  }
}

PlayerName GameState::currentPlayer() const {
  return _current;
}

std::ostream& operator <<(std::ostream& o, const GameState& state) {
  o << "Player: ";
  o << ((state.currentPlayer() == PLAYER_BLACK) ? "Black\n" : "White\n");
  o << "Dice: " << state._dieA+1 << " " << state._dieB+1 << "\n";
  o << state._g;
  o << "Territory for black: ";
  o << state._tBlack;
  o << "Territory for white: ";
  o << state._tWhite;
}
