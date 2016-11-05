#include <cstdlib>
#include <sstream>
#include <cstring>
#include <random>
#include "RoyalClod.h"
#include "GameState.h"

static std::random_device RD_SOURCE;
static std::minstd_rand RD(RD_SOURCE());
static std::uniform_int_distribution<int> DICE(0, 5);

GameState::GameState()
  : _g()
  , _tBlack()
  , _tWhite()
  , _dieA(-1)
  , _dieB(-1)
  , _current(PLAYER_BLACK)
  , _moves()
  , _secondRoll(false)
  , _spacesFilled(0)
{
}

GameState::~GameState() {
}

void GameState::rollDice(int& dieA, int& dieB) {
  _dieA = DICE(RD);
  _dieB = DICE(RD);
  dieA = _dieA;
  dieB = _dieB;

  int subSquaresM = WIDTH/6;
  int subSquaresN = HEIGHT/6;

  for (int m = 0; m < subSquaresM; m++) {
    for (int n = 0; n < subSquaresN; n++) {
      fillCanGo(m,n,_dieA,_dieB);
      fillCanGo(m,n,_dieB,_dieA);
    }
  }

  if (_moves.count() == 0) {
    if (_secondRoll) {
      _secondRoll = false;
      nextPlayer();
    } else {
      _secondRoll = true;
    }
    cleanUpPostTurn();
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

  Move m;
  m.i = x;
  m.j = y;
  m.borderWhite = 0;
  m.borderBlack = 0;

  if (_g(x-1,y) == CELL_BLACK) m.borderBlack += _tBlack(_tBlack(x-1,y));
  if (_g(x+1,y) == CELL_BLACK) m.borderBlack += _tBlack(_tBlack(x+1,y));
  if (_g(x,y-1) == CELL_BLACK) m.borderBlack += _tBlack(_tBlack(x,y-1));
  if (_g(x,y+1) == CELL_BLACK) m.borderBlack += _tBlack(_tBlack(x,y+1));

  if (_g(x-1,y) == CELL_WHITE) m.borderWhite += _tWhite(_tWhite(x-1,y));
  if (_g(x+1,y) == CELL_WHITE) m.borderWhite += _tWhite(_tWhite(x+1,y));
  if (_g(x,y-1) == CELL_WHITE) m.borderWhite += _tWhite(_tWhite(x,y-1));
  if (_g(x,y+1) == CELL_WHITE) m.borderWhite += _tWhite(_tWhite(x,y+1));

  _moves.addMove(m);
}

bool GameState::takeTurn(Move m, PlayerName name) {
  int i = m.i;
  int j = m.j;
  if (name != _current) {
    return false;
  }

  if (_dieA == -1 or _dieB == -1) {
    return false;
  }

  if (_g(i,j) != CELL_CANGO) {
    return false;
  }

  _g(i,j) = playerToCell(name);
  _spacesFilled += 1;
  if (name == PLAYER_BLACK) {
    _tBlack.placeAt(i,j);
  } else {
    _tWhite.placeAt(i,j);
  }

  nextPlayer();
  cleanUpPostTurn();

  return true;
}

bool GameState::isOver() {
  return _spacesFilled == WIDTH*HEIGHT;
}

void GameState::cleanUpPostTurn() {
  _moves.clear();
  _dieA = -1;
  _dieB = -1;
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      if (_g(i,j) == CELL_CANGO) _g(i,j) = CELL_EMPTY;
    }
  }
}

void GameState::nextPlayer() {
  _secondRoll = false;
  _current = opponentPlayer();
}

PlayerName GameState::currentPlayer() const {
  return _current;
}

PlayerName GameState::opponentPlayer() const {
  return ((_current == PLAYER_BLACK) ? PLAYER_WHITE : PLAYER_BLACK);
}

PlayerName GameState::winningPlayer() const {
  int blackSize = _tBlack(_tBlack.largestTerritory());
  int whiteSize = _tWhite(_tWhite.largestTerritory());
  if (blackSize > whiteSize) {
    return PLAYER_BLACK;
  } else {
    return PLAYER_WHITE;
  }
}

CellState GameState::playerToCell(PlayerName player) const {
  if (player == PLAYER_BLACK) {
    return CELL_BLACK;
  } else {
    return CELL_WHITE;
  }
}

MoveList& GameState::moves() {
  return _moves;
}

std::ostream& operator <<(std::ostream& o, const GameState& state) {
  o << state._g;
  return o;
  o << "Player: ";
  o << ((state.currentPlayer() == PLAYER_BLACK) ? "Black\n" : "White\n");
  o << "Current winner: ";
  switch (state.winningPlayer()) {
    case PLAYER_WHITE:
      o << "White\n"; break;
    case PLAYER_BLACK:
      o << "Black\n"; break;
    default:
      o << "???\n"; break;
  } 
  o << "Dice: " << state._dieA+1 << " " << state._dieB+1 << "\n";
  o << state._g;
  return o;
  o << "Territory for black: \n";
  o << state._tBlack;
  o << "Territory for white: \n";
  o << state._tWhite;
}
