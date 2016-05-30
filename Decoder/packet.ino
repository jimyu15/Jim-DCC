uint8_t getPacket(uint8_t buffer[])
{
  int preamble = 0;
  while (readBit())
    preamble++;
  if (preamble < 9)
    return 0;
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
  for (int i = 0; i < count - 1; i++)
    checksum ^= buffer[i];
  if (checksum != buffer[count])
    return 0;
  else
    return count;
}

boolean readBit()
{
  timerCount = 0;
  phase = 0;
  LPM0;
  timerCount = 0;
  LPM0;
  if (timerCount > 65 / MICROS_PER_COUNT)
    return 0;
  else 
    return 1;
}

