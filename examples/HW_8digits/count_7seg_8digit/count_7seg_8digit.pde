/*** Count 7seg8digit


SEG-A(11)    PD4    4
SEG-B(7)     PB0    8
SEG-C(4)     PB3    11
SEG-D (2)    PB5    13
SEG-E(1)     PC0    14
SEG-F(10)    PD5    5
SEG-G(5)     PB2    10
SEG-DP(3)    PB4    12

DIG-1(12)    PD3    3
DIG-2(9)     PD6    6
DIG-3(8)     PD7    7
DIG-4(6)     PB1    9
DIG-5(12)    PC1    15
DIG-6(9)     PC2    16
DIG-7(8)     PC3    17
DIG-8(6)     PC4    18
 */

#include <Sseg.h>


Sseg mySseg = Sseg(4, 8, 11, 13, 14, 5, 10, 12, 3, 6, 7, 9, 15, 16, 17, 18);

long i = 0;

void setup()
{
  mySseg.begin();
  mySseg.setZeroSupress(0);
}

void loop()
{
  if ((++i) > 10000000)
    i=0;
  mySseg.writeNum(i);
  mySseg.updateWithDelay(1);
}

