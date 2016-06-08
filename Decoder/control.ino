
int8_t vSet, vMax, vStart, vMid;
uint8_t acc, dec;
uint32_t vTimer;
float vCurrent;


void controlInit()
{
  vSet = 0;
  vMax = 127;
  vMid = 63;
  vStart = 30;
  acc = 10;
  dec = 8;
  vCurrent = 0;
  vTimer = timer;
}

void speedCal()
{
  uint32_t delta = timer - vTimer;
  if (delta < 100000 / MICROS_PER_COUNT || delta > 3000000 / MICROS_PER_COUNT)
    return;

  int a;

  if (abs(vCurrent - vSet) < 0.5)
    a = 0;
  else if (vCurrent > vSet)
  {
    if (vCurrent > 0)
      a = -1 * dec;
    else
      a = -1 * acc;
  }
  else
  {
    if (vCurrent > 0)
      a = acc;
    else
      a = dec;
  }

  if (a == 0)
    vCurrent = vSet;
  else 
    vCurrent += delta * MICROS_PER_COUNT / 0.007 / a / 1000000;

  #ifdef MOTOR
  if (vCurrent >= 0)
    P1OUT |= PH;
  else
    P1OUT &= ~PH;
  if (abs(vCurrent) < 1)
    CCR1 = 0;
  else if (abs(vCurrent) < 64)
    CCR1 = vStart + abs(vCurrent) * (vMid - vStart) / 64;
  else
    CCR1 = min(vMax, vMid + (float)(vMax - vMid) * (abs(vCurrent) - 64) / 64);
  #endif
  
  vTimer += delta;

  #ifdef DEBUG
  Serial.print("\tCurrent speed: ");
  Serial.print(vCurrent, DEC);
  Serial.print("\tTarget speed: ");
  Serial.print(vSet, DEC);
  Serial.print("\tCCR1: ");
  Serial.println(CCR1, DEC);
  #endif
  
  
}

inline void speedSet(int v)
{
  vSet = constrain(v, -128, 127);
  #ifdef DEBUG
  Serial.print("Set speed:");
  Serial.println(vSet, DEC);
  #endif
}
