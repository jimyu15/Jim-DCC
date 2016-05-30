void interruptInit()
{
  __dint();
  P1IES |= IN1 + IN2;
  P1IFG &= ~(IN1 + IN2);
  P1IE = IN1;
  __eint();

}

void interruptEnable();
void interruptDisable();

__attribute__((interrupt(PORT1_VECTOR)))
void Port_1(void)
{
  if (P1IFG & IN1)
  {
    if (P1IN & IN2)// Prevent VCC drop to zero
    {
      if (sleepingMode)
      {
        sleepingMode = 0;
        P1OUT |= NSLEEP;
        LPM4_EXIT;
      }
      else if (phase);
      LPM0_EXIT;
    }
    P1IE = IN2;
    P1IFG &= ~IN1;
  }
  
  if (P1IFG & IN2)
  {
    if (P1IN & IN1)// Prevent VCC drop to zero
    {
      if (sleepingMode)
      {
        sleepingMode = 0;
        P1OUT |= NSLEEP;
        LPM4_EXIT;
      }
      else if (!phase);
      LPM0_EXIT;
    }
    P1IE = IN1;
    P1IFG &= ~IN2;
  }
}

