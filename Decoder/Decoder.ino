#include "decoder.h"

uint8_t sleepingMode = 0, buffer[10];
uint16_t timerCount = 0, addr;
uint32_t timer = 0;
boolean phase = 0;

void setup()
{
  pinInit();
  timerInit();
  interruptInit();
  eepromInit();
}


void loop()
{
  int packetCount = getPacket(buffer), packetPos = 0;
  if (packetCount > 3)
  {
    
    if (buffer[0] == 0)
    {
      packetPos++;
      //broadcast
    }
    else if (buffer[0] * 256 + buffer[1] == addr)
    {
      packetPos += 2;
    }
    if (packetPos)
    {
      switch(buffer[packetPos] >> 5)
      {
        case 0:
        //000 Decoder and Consist Control Instruction
        break;
        
        case 1:
        //001 Advanced Operation Instructions
        if (buffer[packetPos] & B00011111)
          //setSpeed(buffer[packetPos + 1]);
        if (buffer[packetPos] & B00011111)
          //maxSpeed = buffer[packetPos + 1];
        packetPos += 2;
        break;
        
        case 2:
        //010 Speed and Direction Instruction for reverse operation
        break;
        
        case 3:
        //011 Speed and Direction Instruction for forward operation
        break;
        
        case 4:
        //100 Function Group One Instruction
        break;
        
        case 5:
        //101 Function Group Two Instruction
        break;
        
        case 7:
        //111 Configuration Variable Access Instruction
        break;
        
        default:
        break;
      }
    }
  }
}









