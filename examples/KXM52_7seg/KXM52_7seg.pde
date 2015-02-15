/*** Accelerometer KXM52

SEG-A(11)    PD4    4
SEG-B(7)     PB0    8
SEG-C(4)     PB3    11
SEG-D (2)    PB5    13
SEG-E(1)     PC0    14
SEG-F(10)    PD2    2  ** Change on V2
      was SEG-F(10)    PD5    5  ** V1
SEG-G(5)     PB2    10
SEG-DP(3)    PB4    12

DIG-1(12)    PD3    3
DIG-2 (9)    PD6    6
DIG-3 (8)    PD7    7
DIG-4 (6)    PB1    9

ACCEL X -> A3
ACCEL Y -> A4
ACCEL Z -> A5


 */

#include <Sseg.h>

int aport_x = 3;
int aport_y = 4;
int aport_z = 5;

int val_x, val_y, val_z;

Sseg mySseg = Sseg(4, 8, 11, 13, 14, 2, 10, 12, 3, 6, 7, 9);
// Sseg mySseg = Sseg(4, 8, 11, 13, 14, 5, 10, 12, 3, 6, 7, 9);

void setup()
{

  mySseg.begin();
  mySseg.setZeroSupress(0);
}

void loop()
{
  val_x = analogRead(aport_y);
  mySseg.writeNum(val_x);   
  mySseg.updateWithDelay(100);
}

