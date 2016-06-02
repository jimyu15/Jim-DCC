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
      buffer[count] |= readBit();
      buffer[count] <<= 1;
    }
    count++;
  } while (readBit() == 0);
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

