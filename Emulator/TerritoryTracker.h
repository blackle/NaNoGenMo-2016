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
  int8_t operator()(int i, int j) const;
private:
  friend std::ostream& operator <<(std::ostream& o, const TerritoryTracker& tracker);
  int8_t& operator()(int i, int j);
  void replaceAll(int8_t i, int8_t j);

  int _w;
  int _h;
  int8_t* _states;
  int8_t _fill;
  int8_t _maxId;
};


#endif
