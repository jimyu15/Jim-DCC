#include "decoder.h"

uint8_t sleepingMode = 0, buffer[10];
uint16_t timerCount = 0, addr;
uint32_t timer = 0;
boolean phase = 0;

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  delay(500);
  #endif
  
  pinInit();
  timerInit();
  interruptInit();
  eepromInit();
  controlInit();
  
}


void loop()
{
  int packetCount = getPacket(buffer);
  if (packetCount > 3)
    readPacket(packetCount);
  
  #ifdef LOCO
  speedCal();
  #endif
}









