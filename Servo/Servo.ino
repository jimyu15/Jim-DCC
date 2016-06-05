uint32_t t1, t2;
uint16_t stat[6] = {24000,24000,24000,24000,24000,24000};
uint16_t limit[12] = {
	28000, 20000,
	28000, 20000,
	28000, 20000,
	28000, 20000,
	28000, 20000,
	28000, 20000,
};

void setup()
{
	Serial.begin(115200);
	for (int i = 8; i < 14; i++)
		pinMode(i, OUTPUT);
	pinMode(2, OUTPUT);
	P2OUT = 0;
	t1 = millis();
}

void loop()
{
	
	while (micros() - t1 < 20000)
	{
		if (Serial.read() == '<')
		{
			Serial.println("<");
			delayMicroseconds(1000);
			if (Serial.read() == 'Y')
			{
				Serial.println("Y");
				delayMicroseconds(1000);
				uint8_t id = Serial.read();
				Serial.println(id);
				delayMicroseconds(1000);
				if (id < '7' && id >= '0' && Serial.read() == ' ')
				{
					Serial.println(' ');
					delayMicroseconds(1000);
					uint8_t temp = Serial.read();
					Serial.println(temp);
					if (temp == '0')
					{
						stat[id - '0'] = limit[(id - '0') * 2];
						Serial.println(stat[id - '0']);
					}
					if (temp == '1')
					{
						stat[id - '0'] = limit[(id - '0') * 2 + 1];
					}
					for (int i = 0; i < 6; i++)
  					{
  						Serial.print(stat[i]);
  						Serial.print("\t");

  					}
  					Serial.println();
				}
			}
		}

	}
	t1 = micros();
	P2OUT = B00111111;

	CCR0 = 40000-1;             // PWM Period
  	TACTL = MC_1 | ID_0 | TASSEL_2 | TACLR;   // SMCLK, up mode
  	while (TAR < 32000)
  	{
  		uint8_t out = 0;
  		for (int i = 0; i < 6; i++)
  		{
  			out <<= 1;
  			if (stat[5 - i] > TAR)
  				out |= 1;
  		}
  		P2OUT = out;
  		P1OUT ^= BIT0;
  	}
  	P2OUT = 0;
  	
  	
}