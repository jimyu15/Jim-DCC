uint8_t cv[2] = {0};

uint8_t getPacket(uint8_t buffer[])
{
  int i = 0;
  int preamble = 0;
  while (preamble < 9)
  {
    preamble = 0;
    while (readBit())
      preamble++;
    if (i++ > 5)
      return 0;
  }
  int count = 0;
  do
  {
    for (int i = 0; i < 8; i++)
    {
      buffer[count] <<= 1;
      buffer[count] |= readBit();
    }
    count++;
  } 
  while (readBit() == 0);
  uint8_t checksum = 0;
  for (int i = 0; i < count; i++)
    checksum ^= buffer[i];
  if (checksum != 0)
    return 0;
  else
    return count;
}

boolean readBit()
{
  timerCount = 0;
  __delay_cycles(4);  //wait for interrupt flag
  LPM0;
  timerCount = 0;
  __delay_cycles(4);  //wait for interrupt flag
  LPM0;
  if (timerCount > 65 / MICROS_PER_COUNT)
    return 0;
  else 
    return 1;
}

uint8_t readPacket(int count)
{
  int packetPos = 0;
  if (buffer[0] == 0)
  {
    packetPos++;
    //broadcast
  }
  else if (addr < 128)
  {
    if (buffer[0] == addr)
      packetPos++;
    else
      return 0;
  }
  else 
  {
    if (buffer[0] * 256 + buffer[1] == addr)
      packetPos += 2;
    else
      return 0;
  }
  if (packetPos)
  {
    P1OUT ^= LED;
    switch(buffer[packetPos] >> 5)
    {
    case 0:
      //000 Decoder and Consist Control Instruction
      if (buffer[packetPos] == 0)
        controlInit();
      break;

    case 1:
      //001 Advanced Operation Instructions
      if (buffer[packetPos] & B00011111 == B00011111)
      {
        speedSet(buffer[packetPos + 1]);
      }
      if (buffer[packetPos] & B00011111 == B00011110)
        vMax = buffer[packetPos + 1] & B01111111;
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
      #ifdef F1
      if (buffer[packetPos] & BIT0)
        P1OUT |= F1;
      else
        P1OUT &= ~F1;
      #endif

      #ifdef F2
      if (buffer[packetPos] & BIT1)
        P1OUT |= F2;
      else
        P1OUT &= ~F2;
      #endif

      #ifdef F3
      if (buffer[packetPos] & BIT2)
        P1OUT |= F3;
      else
        P1OUT &= ~F3;
      #endif

      #ifdef F4
      if (buffer[packetPos] & BIT3)
        P1OUT |= F4;
      else
        P1OUT &= ~F4;
      #endif

      #ifdef FL
      if (buffer[packetPos] & BIT4)
        P1OUT |= FL;
      else
        P1OUT &= ~FL;
      #endif

      #ifdef DEBUG
      Serial.println(buffer[packetPos] & B00011111, BIN);
      #endif
      break;

    case 5:
      //101 Function Group Two Instruction


      break;

    case 7:
      //111 Configuration Variable Access Instruction
      if (buffer[packetPos] == 0xEC)
      {
        if (cv[0] == 0 && cv[1] == 0)
        {
          cv[0] = buffer[packetPos + 1];
          cv[1] = buffer[packetPos + 2];
        }
        else if (cv[0] == buffer[packetPos + 1] && cv[1] == buffer[packetPos + 2])
        {
          write8(cv[0], cv[1]);
          
          #ifdef DEBUG
          Serial.print("CV");
          Serial.print(cv[0], DEC);
          Serial.print(": ");
          Serial.println(cv[1], DEC);
          #endif

          cv[0] = 0;
          cv[1] = 0;
          controlInit();
        }
      }

      break;

    default:
      break;
    }
  }
}



