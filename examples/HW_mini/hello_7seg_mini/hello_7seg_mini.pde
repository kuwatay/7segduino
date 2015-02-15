/*** Hello 7seg for mini 7seg

NOTE: To use this application, arduino-core must be RCduino

SEG-A(15)    PB6    20 (Extended)
SEG-B(16)    PD5    5
SEG-C(13)    PD3    3
SEG-D (3)    PB2    10
SEG-E (5)    PB3    11
SEG-F(11)    PD4    4
SEG-G(15)    PB7    21 (Extended)
SEG-DP(7)    PC1    15

DIG-1 (1)    PB4    12
DIG-2 (2)    PB5    13
DIG-3 (6)    PC0    14
DIG-4 (8)    PC2    16

 */

#include <Sseg.h>


Sseg mySseg = Sseg(20, 5, 3, 10, 11, 4, 21, 15, 12, 13, 14, 16);

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
    OVERWRAP(hello, p+1),  
    OVERWRAP(hello, p+2),  
    OVERWRAP(hello, p+3));

  mySseg.updateWithDelay(500);

}

