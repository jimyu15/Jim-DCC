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
    switch(buffer[packetPos] >> 5)
    {
    case 0:
      //000 Decoder and Consist Control Instruction
      break;

    case 1:
      //001 Advanced Operation Instructions
      if (buffer[packetPos] & B00011111)
      {
        speedSet(buffer[packetPos + 1]);
      }
      if (buffer[packetPos] & B00011110)
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



