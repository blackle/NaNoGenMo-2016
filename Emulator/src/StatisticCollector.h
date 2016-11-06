#ifndef __STATISTIC_COLLECTOR__
#define __STATISTIC_COLLECTOR__
#include <thread>
#include <mutex>
#include "Brain.h"

class StatisticCollector {
public:
  StatisticCollector(Brain& b);
  ~StatisticCollector();
  float collectStats();
private:
  Brain& _b;
  int _blackSampleTotal;
  int _whiteSampleTotal;
};

#endif