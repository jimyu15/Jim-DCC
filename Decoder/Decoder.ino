#include "decoder.h"

uint8_t sleepingMode = 0, buffer[10];
uint16_t timerCount = 0, addr;
uint32_t timer = 0;
boolean phase = 0;

void setup()
{
  #ifdef DEBUG
  Serial.begin(9600);
  Serial.println("HI");
  delay(500);
  #endif
  
  pinInit();
  eepromInit();
  timerInit();
  
  interruptInit();
  controlInit();
  timerEnable();
  
}


void loop()
{
  #ifdef DEBUG
  int packetCount = 0;
  while (Serial.available() && packetCount < 9)
  {
    buffer[packetCount] = Serial.read();
    if (buffer[packetCount] == '/n')
      break;
    else
      packetCount++;
    __delay_cycles(16000);
  }
  if (packetCount)
  {
    for (int i = 0; i < packetCount; i++)
    {
      Serial.print(buffer[i], HEX);
      Serial.print("\t");
    }
    Serial.println("\t");
  }
  #else
  int packetCount = getPacket(buffer);
  #endif
  if (packetCount >= 3)
    readPacket(packetCount);
  
  speedCal();
}





