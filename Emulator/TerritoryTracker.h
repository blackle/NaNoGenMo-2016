#ifndef __TERRITORY_TRACKER__
#define __TERRITORY_TRACKER__
#include <iostream>
#include <sstream>
#include <stdint.h>

class TerritoryTracker {
public:
  TerritoryTracker(int w, int h);
  ~TerritoryTracker();
  int width() const;
  int height() const;
  void placeAt(int i, int j);
  const int8_t operator()(int i, int j) const;
  const uint8_t operator()(int n) const;
  int largestTerritory() const;
  int8_t& operator()(int i, int j);
private:
  friend std::ostream& operator <<(std::ostream& o, const TerritoryTracker& tracker);
  void replaceAll(int8_t i, int8_t j);

  int _w;
  int _h;
  int8_t* _states;
  uint8_t* _idSizes;
  int8_t _fill;
  int8_t _maxId;
};


#endif
