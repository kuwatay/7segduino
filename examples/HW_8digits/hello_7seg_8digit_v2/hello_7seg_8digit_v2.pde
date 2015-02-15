/*** Hello 7seg 2digit


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
  for (i = 0 ; i <4; i++) {
    mySseg.writeRawData(
      OVERWRAP(hello, p),
      OVERWRAP(hello, p+1),  
      OVERWRAP(hello, p+2),  
      OVERWRAP(hello, p+3),
      OVERWRAP(hello, p+4),
      OVERWRAP(hello, p+5),  
      OVERWRAP(hello, p+6),  
      OVERWRAP(hello, p+7));
  }    

  mySseg.updateWithDelay(300);

}

