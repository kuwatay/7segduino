/*** simple_switch

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

 */

#include <Sseg.h>

int switch_pin = 19;
Sseg mySseg = Sseg(4, 8, 11, 13, 14, 2, 10, 12, 3, 6, 7, 9);
// Sseg mySseg = Sseg(4, 8, 11, 13, 14, 5, 10, 12, 3, 6, 7, 9);

void setup()
{
  pinMode (switch_pin, INPUT);
  digitalWrite(switch_pin, HIGH);

  mySseg.begin();
  mySseg.setZeroSupress(0);
}

void loop()
{
  int switch_status;
  static int pre_status = HIGH;
  static int count = 0;
  
  switch_status = digitalRead(switch_pin);
  
  if (switch_status == LOW) {
    if (pre_status == HIGH) {
      count++;
    }
    mySseg.writeNum(count);   
  } else {
    mySseg.writeRawData(0b00000010,0b00000010,0b00000010,0b00000010);
  }
  pre_status = switch_status;

  mySseg.updateWithDelay(100);

}

