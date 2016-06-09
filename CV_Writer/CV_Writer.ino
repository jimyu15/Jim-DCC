#include "cv.h"

void setup()
{
	//Serial.begin(9600);
	eepromInit();
	write8(CV_PRI_ADDR, 28);
	write8(CV_VSTART, 25);
	write8(CV_ACC_RATE, 10);
	write8(CV_DEC_RATE, 4);
	write8(CV_VHIGH, 120);
	write8(CV_VMID, 60);
}

void loop()
{

}