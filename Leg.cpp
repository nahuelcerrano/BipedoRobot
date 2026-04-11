#include "Leg.h"

Leg::Leg() :
  hip(PIN_L_HIP, L_HIP_MIN, L_HIP_MAX, L_HIP_START),
  knee(PIN_L_KNEE, L_KNEE_MIN, L_KNEE_MAX, L_KNEE_START),
  ankle(PIN_L_ANKLE, L_ANKLE_MIN, L_ANKLE_MAX, L_ANKLE_START)
{
}

void Leg::begin() {
  hip.begin();
  knee.begin();
  ankle.begin();
}

void Leg::resetToStart() {
  hip.setAngle(L_HIP_START);
  knee.setAngle(L_KNEE_START);
  ankle.setAngle(L_ANKLE_START);
}
