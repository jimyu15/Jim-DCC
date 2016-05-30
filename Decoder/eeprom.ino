#include <Wire.h>
#define rom_addr 0x50

void write8(uint8_t addr, uint8_t data)
{
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
  delay(1);
}

void write16(uint8_t addr, uint16_t data)
{
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.write((data >> 8) & 0xFF);
  Wire.write(data & 0xFF);
  Wire.endTransmission();
  delay(1);
}

uint8_t read8(uint8_t addr)
{
  uint8_t data = 0;
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(rom_addr, 1);
  data = Wire.read();
  return data;
}

uint16_t read16(uint16_t addr)
{
  uint16_t data = 0;
  Wire.beginTransmission(rom_addr);
  Wire.write(addr);
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(rom_addr, 1);
  data = (Wire.read() << 8) | Wire.read();
  return data;
}

void eepromInit()
{
  Wire.begin();
  addr = read
}
