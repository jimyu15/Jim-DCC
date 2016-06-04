#ifdef LOCO
#define DIR
int8_t vSet, vCurrent, vMax, vStart, vMid, acc, dec, dir;
uint32_t vTimer;
#endif

void controlInit()
{
  vSet = 0;
  vCurrent = 0;
  dir = 1;
  vTimer = timer;
}

void speedCal()
{
  uint32_t delta = timer - vTimer;
  if (vCurrent > vSet)
  {
    vCurrent -= (uint32_t)(vCurrent > 0 ? dec : acc) * delta * MICROS_PER_COUNT / 1000000;
    vCurrent = max(vCurrent, vSet);
  }
  else
  {
    vCurrent += (uint32_t)(vCurrent < 0 ? dec : acc) * delta * MICROS_PER_COUNT / 1000000;
    vCurrent = min(vCurrent, vSet);
  }
  if (vCurrent < 64)
    CCR1 = (float)(vMid - vStart) * abs(vCurrent) / 64;
  else
    CCR1 = max(127, vMid + (float)(vMax - vMid) * (abs(vCurrent) - 64) / 64);
  vTimer += delta;
  
  #ifdef DEBUG
  Serial.print("Current speed:");
  Serial.print(vCurrent, DEC);
  Serial.print("\tTarget speed:");
  Serial.println(vSet, DEC);
  #endif
}

inline void speedSet(uint8_t v)
{
  vSet = v;
  #ifdef DEBUG
  Serial.print("Set speed:");
  Serial.println(vSet, DEC);
  #endif
}
