#define TEST_LED 0
#define TEST_EEPROM 0
#define TEST_INPUT 0
#define TEST_MOTOR 0
#define TEST_FUNC 0

void testing()
{
	if (TEST_LED)
		while(1)
		{
			P1OUT ^= LED;
			delay(1000);
		}
	else if(TEST_INPUT)
	{
		P1OUT |= LED;
		int ct = 0;

		while(1)
		{
			while(P1IN & IN1);
			while(P1IN & IN2);
			while(P1IN & IN1);
			ct++;
			if (ct > 10000)
			{
				P1OUT ^= LED;
				ct = 0;
			}


		}
	}
	else if (TEST_FUNC)
	{
		enableWatchDog();
		#ifdef HEADLIGHT
		P1OUT |= EN1;
		while(1)
		{
			
			P1OUT ^= EN1 + EN2;
			delay(1000);

		}
		#endif


		

	}
}
