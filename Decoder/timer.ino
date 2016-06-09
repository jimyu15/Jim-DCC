void timerInit()
{
  disableWatchDog();
  CCR0 = 128-1;             // PWM Period
  #ifdef MOTOR
  CCTL1 = OUTMOD_7;          // CCR1 reset/set
  #endif
  CCR1 = 0;                // CCR1 PWM duty cycle
  TACTL = MC_1 | ID_0 | TASSEL_2 | TACLR;   // SMCLK, up mode
  
}

inline void timerEnable()
{
  TACCTL0 |= CCIE;
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
  if (timerCount > SHUTDOWN_TIMEOUT / MICROS_PER_COUNT)
  {
    sleepingMode = 1;
    #ifdef MOTOR
    P1OUT &= ~(NSLEEP + LED);
    #else
    P1OUT &= ~LED;
    #endif

    __bis_status_register(LPM4_bits+GIE);;
  }
  #endif
    
}

