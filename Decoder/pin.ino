void pinInit()
{
  P1DIR = LED;
  #ifdef MOTOR
  P1DIR |= NSLEEP + EN + PH;
  P1SEL |= EN;
  P1OUT = NSLEEP;
  #endif
  #ifdef F1
  P1DIR |= F1;
  #endif
  #ifdef F2
  P1DIR |= F2;
  #endif
}
