void pinInit()
{
  P1DIR = EN + PH + NSLEEP + LED;
  P1SEL |= EN;             // P1.2 to TA0.1
  P1OUT = NSLEEP;
}
