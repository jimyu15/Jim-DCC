
#include <Wire.h>

int8_t vSet, vMax, vStart, vMid;
uint8_t acc, dec;
uint32_t vTimer;
float vCurrent;


void controlInit()
{
  addr = read8(CV_PRI_ADDR);
  vSet = 0;
  vMax = constrain(read8(CV_VHIGH), 60, 127); 
  vMid = constrain(read8(CV_VMID), 20, 120);
  vStart = constrain(read8(CV_VSTART), 0, 60);
  acc = constrain(read8(CV_ACC_RATE), 0, 50);
  dec = constrain(read8(CV_DEC_RATE),0, 50);
  vCurrent = 0;
  vTimer = timer;
  #ifdef DEBUG
  Serial.print("vMax:");
  Serial.print(vMax, DEC);
  Serial.print("\tvMid: ");
  Serial.print(vMid, DEC);
  Serial.print("\tvStart: ");
  Serial.print(vStart, DEC);
  Serial.print("\tacc: ");
  Serial.print(acc, DEC);
  Serial.print("\tdec: ");
  Serial.println(dec, DEC);
  #endif
}

void speedCal()
{
  uint32_t delta = timer - vTimer;
  if (delta < 100000 / MICROS_PER_COUNT || delta > 3000000 / MICROS_PER_COUNT)
    return;

  int a;
  

  if (abs(vCurrent - vSet) <= 1 || (abs(vCurrent) <= 1 && abs(vSet) <= 1))
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
  if (abs(vCurrent) <= 1)
    CCR1 = 0;
  else if (abs(vCurrent) < 64)
    CCR1 = vStart + abs(vCurrent) * (vMid - vStart) / 64;
  else
    CCR1 = min(vMax, vMid + (float)(vMax - vMid) * (abs(vCurrent) - 64) / 63);
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

void speedSet(int v)
{
  vSet = max(v & 0x7F, 1);
  if (~v & 0x80)
    vSet *= -1;
  #ifdef DEBUG
  Serial.print("Set speed:");
  Serial.println(vSet, DEC);
  #endif
}
