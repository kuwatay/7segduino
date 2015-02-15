/*** Hello 7seg 2digit

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

uint8_t hello[] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b01101110, // H
  0b10011110, // E
  0b00011100, // L
  0b00011100, // L
  0b00111010, // o
  0b00000000, // 
  NUM_PAT_7,  // 7
  0b10110110, // S
  NUM_PAT_E,  // E
  0b11110110, // G
  0b00000001
};

int p = 0;
void setup()
{
  mySseg.begin();

// mySseg.writeRawData(NUM_PAT_0, NUM_PAT_1, NUM_PAT_2, NUM_PAT_3);
// mySseg.writeRawData(NUM_PAT_4, NUM_PAT_5, NUM_PAT_6, NUM_PAT_7);
//  mySseg.writeRawData(NUM_PAT_8, NUM_PAT_9, NUM_PAT_A, NUM_PAT_B);
//  mySseg.writeRawData(NUM_PAT_C, NUM_PAT_D, NUM_PAT_E, NUM_PAT_F);
  
//  mySseg.writeNum(1, 2, 0xa, 4);


}

#define OVERWRAP(a, x) (((x) < sizeof(a)) ? (a[(x)]) : a[((x) - sizeof(a))])
void loop()
{
  uint8_t i;
  if ((++p) > sizeof(hello))
    p = 0;
  mySseg.writeRawData(
    OVERWRAP(hello, p),
    OVERWRAP(hello, p+1));

  mySseg.updateWithDelay(300);

}

