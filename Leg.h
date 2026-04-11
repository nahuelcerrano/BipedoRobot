#ifndef LEG_H
#define LEG_H

#include "Joint.h"
#include "Config.h"

class Leg {
  public:
    Joint hip;
    Joint knee;
    Joint ankle;

    Leg();

    void begin();
    void resetToStart();
};

#endif