#include <cstdlib>
#include <sstream>
#include <cstring>
#include "TerritoryTracker.h"

#define EMPTY -1

TerritoryTracker::TerritoryTracker(int w, int h) 
  : _w(w)
  , _h(h)
  , _maxId(0)
{
  int totalcells = w*h;
  size_t statesSize = sizeof(int8_t)*totalcells;
  _states = (int8_t*)malloc(statesSize);
  std::memset(_states, EMPTY, statesSize);
}

TerritoryTracker::~TerritoryTracker() {
  free(_states);
}

int TerritoryTracker::width() const {
  return _w;
}

int TerritoryTracker::height() const {
  return _h;
}

void TerritoryTracker::placeAt(int i, int j) {
  int8_t east = (*this)(i-1,j);
  int8_t west = (*this)(i+1,j);
  int8_t north = (*this)(i,j+1);
  int8_t south = (*this)(i,j-1);
  
  int8_t minId = north;
  minId = ((minId == EMPTY) ? south : ((south != EMPTY && south < minId) ? south : minId));
  minId = ((minId == EMPTY) ? east : ((east != EMPTY && east < minId) ? east : minId));
  minId = ((minId == EMPTY) ? west : ((west != EMPTY && west < minId) ? west : minId));

  if (minId == EMPTY) {
    (*this)(i,j) = _maxId;
    _maxId++;
    return;
  }

  (*this)(i,j) = minId;
  if (north != EMPTY) replaceAll(north, minId);
  if (south != EMPTY) replaceAll(south, minId);
  if (east != EMPTY) replaceAll(east, minId);
  if (west != EMPTY) replaceAll(west, minId);
}

void TerritoryTracker::replaceAll(int8_t oldId, int8_t newId) {
  for (int j = 0; j < _h; j++) {
    for (int i = 0; i < _w; i++) {
      int8_t cellval = (*this)(i,j);
      if (cellval == oldId) {
        (*this)(i,j) = newId;
      }
    }
  }
}

int8_t TerritoryTracker::operator()(int i, int j) const {
  if (i < 0 or i >= _w) {
    return EMPTY;
  }
  if (j < 0 or j >= _h) {
    return EMPTY;
  }
  return _states[i*_h+j];
}

int8_t& TerritoryTracker::operator()(int i, int j) {
  _fill = EMPTY;
  if (i < 0 or i >= _w) {
    return _fill;
  }
  if (j < 0 or j >= _h) {
    return _fill;
  }
  return _states[i*_h+j];
}

std::ostream& operator <<(std::ostream& o, const TerritoryTracker& tracker) {
  for (int j = 0; j < tracker.height(); j++) {
    for (int i = 0; i < tracker.width(); i++) {
      int8_t zone = tracker(i,j);
      switch (zone) {
        case EMPTY:
          o << "  "; break;
        case 0:
          o << " 0"; break;
        case 1:
          o << " 1"; break;
        case 2:
          o << " 2"; break;
        default:
          o << " ?"; break;
      }
    }
    std::cout << "\n";
  }
}
