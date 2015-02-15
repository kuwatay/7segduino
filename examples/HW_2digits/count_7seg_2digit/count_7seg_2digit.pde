/*** Count 7seg

LED = SN230502

SEG-A(7)     PD4    4
SEG-B(6)     PB0    8
SEG-C(4)     PB3    11
SEG-D (1)    PB5    13
SEG-E(3)     PC0    14
SEG-F(8)     PD5    5
SEG-G(9)     PB2    10
SEG-DP(2)    PB4    12

DIG-1(10)    PD3    3
DIG-2 (5)    PD6    6

 */

#include <Sseg.h>


Sseg mySseg = Sseg(4, 8, 11, 13, 14, 5, 10, 12, 3, 6);

int i = 0;

void setup()
{
  mySseg.begin();
}

void loop()
{
  if ((++i) > 100)
    i=0;
  mySseg.writeNum(i);
  mySseg.updateWithDelay(1000);
}

