void timerInit()
{
  disableWatchDog();
  CCR0 = 128-1;             // PWM Period
  #ifdef MOTOR
  CCTL1 = OUTMOD_7;          // CCR1 reset/set
  #endif
                  // CCR1 PWM duty cycle
  TACTL = MC_1 | ID_0 | TASSEL_2 | TACLR;   // SMCLK, up mode
  
}

inline void timerEnable()
{
  TACCTL0 |= CCIE;
  CCR1 = 0;
}

inline void timerDisable()
{
  TACCTL0 &= ~CCIE;
}

__attribute__((interrupt(TIMER0_A0_VECTOR)))
static void TA0_ISR(void)
{
  timer++;
  timerCount++;
  
  #ifndef DEBUG
  if (sleepingMode == 1)
  {
    LPM3_EXIT;

  }
  else if (timerCount > SHUTDOWN_TIMEOUT / MICROS_PER_COUNT)
  {
    sleepingMode = 1;
    #ifdef MOTOR
    P1OUT &= ~(NSLEEP + LED);
    #else
    P1OUT &= ~LED;
    #endif
    CCR0 = 600;
    TACTL = MC_1 | ID_3 | TASSEL_1 | TACLR;
    __bis_status_register(LPM3_bits+GIE);;
  }
  #endif
    
}

