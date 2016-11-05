#include <cstdlib>
#include <sstream>
#include <cstring>
#include <iomanip>
#include "RoyalClod.h"
#include "TerritoryTracker.h"

#define EMPTY -1

TerritoryTracker::TerritoryTracker() 
  : _maxId(0)
{
  int totalcells = WIDTH*HEIGHT;
  size_t statesSize = sizeof(int8_t)*totalcells;
  _states = (int8_t*)malloc(statesSize);
  std::memset(_states, EMPTY, statesSize);

  size_t idSizesSize = sizeof(uint8_t)*totalcells;
  _idSizes = (uint8_t*)malloc(idSizesSize);
  std::memset(_idSizes, 0, idSizesSize);
}

TerritoryTracker::~TerritoryTracker() {
  free(_states);
  free(_idSizes);
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
    _idSizes[_maxId] += 1;
    _maxId++;
    return;
  }

  (*this)(i,j) = minId;
  _idSizes[minId] += 1;
  
  if (north != EMPTY) replaceAll(north, minId);
  if (south != EMPTY) replaceAll(south, minId);
  if (east != EMPTY) replaceAll(east, minId);
  if (west != EMPTY) replaceAll(west, minId);
}

void TerritoryTracker::replaceAll(int8_t oldId, int8_t newId) {
  if (oldId == newId) {
    return;
  }
  _idSizes[newId] += _idSizes[oldId];
  _idSizes[oldId] = 0;
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int8_t cellval = (*this)(i,j);
      if (cellval == oldId) {
        (*this)(i,j) = newId;
      }
    }
  }
}

const int8_t TerritoryTracker::operator()(int i, int j) const {
  if (i < 0 or i >= WIDTH) {
    return EMPTY;
  }
  if (j < 0 or j >= HEIGHT) {
    return EMPTY;
  }
  return _states[i*HEIGHT+j];
}

int8_t& TerritoryTracker::operator()(int i, int j) {
  _fill = EMPTY;
  if (i < 0 or i >= WIDTH) {
    return _fill;
  }
  if (j < 0 or j >= HEIGHT) {
    return _fill;
  }
  return _states[i*HEIGHT+j];
}

const uint8_t TerritoryTracker::operator()(const int n) const {
  return _idSizes[n];
}

int TerritoryTracker::largestTerritory() const {
  uint8_t currMaxVal = 0;
  int currMaxIndex = 0;
  for (int n = 0; n < HEIGHT*WIDTH; n++) {
    if (currMaxVal < _idSizes[n]) {
      currMaxVal = _idSizes[n];
      currMaxIndex = n;
    }
  }
  return currMaxIndex;
}

std::ostream& operator <<(std::ostream& o, const TerritoryTracker& tracker) {
  std::ios init(NULL);
  init.copyfmt(o);
  for (int j = 0; j < HEIGHT; j++) {
    for (int i = 0; i < WIDTH; i++) {
      int8_t zone = tracker(i,j);
      if (zone == EMPTY) {
        o << "   ";
      } else {
        o << std::setw(2) << std::setfill('0') << std::hex << (int)zone << " ";
      }
    }
    std::cout << "\n";
  }
  o.copyfmt(init);
  o << "enumerated:\n";
  for (int k = 0; k < HEIGHT*WIDTH; k++) {
    uint8_t size = tracker(k);
    if (size > 0) {
      o << std::setw(2) << std::setfill('0') << std::hex << k << ": ";
      o.copyfmt(init);
      o << (int)size << "\n";
    }
  }
}
