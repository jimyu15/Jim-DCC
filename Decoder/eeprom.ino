#include <Wire.h>
#define rom_addr 0x50

void write8(uint8_t addr, uint8_t data)
{
  enableWatchDog();
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
  disableWatchDog();
  __delay_cycles(80000);
}

void write16(uint8_t addr, uint16_t data)
{
  enableWatchDog();
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.write((data >> 8) & 0xFF);
  Wire.write(data & 0xFF);
  Wire.endTransmission();
  disableWatchDog();
  __delay_cycles(80000);
}

uint8_t read8(uint8_t addr)
{
  enableWatchDog();
  uint8_t data = 0;
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(rom_addr, 1, 1);
  disableWatchDog();
  return Wire.read();
}

uint16_t read16(uint16_t addr)
{
  enableWatchDog();
  uint16_t data = 0;
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(rom_addr, 2, 1);
  disableWatchDog();
  return (Wire.read() << 8) | Wire.read();
}

void eepromInit()
{
  Wire.begin();
  __delay_cycles(100000);
  disableWatchDog();
}
