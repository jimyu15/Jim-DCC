void pinInit()
{
  P1DIR = EN + PH + NSLEEP + LED;
  P1SEL |= EN;             // P1.2 to TA0.1
  P1REN = IN1 + IN2;
  P1OUT = IN1 + IN2;
}
