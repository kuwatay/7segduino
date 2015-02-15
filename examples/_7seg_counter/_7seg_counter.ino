/*** 7seg counter

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

Sseg mySseg = Sseg(4, 8, 11, 13, 14, 2, 10, 12, 3, 6, 7, 9);
// Sseg mySseg = Sseg(4, 8, 11, 13, 14, 5, 10, 12, 3, 6, 7, 9);

uint8_t flag = 0;
int cnt = 0;
int inc = 1;
uint8_t keyStatus[] = { LOW, LOW, LOW} ;
uint8_t keyChange[] = { 0, 0, 0};

void setup() {
  mySseg.begin();
  pinMode(A1, INPUT);
  digitalWrite(A1, HIGH);
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);
  pinMode(A3, INPUT);
  digitalWrite(A3, HIGH);

}

void loop() {
  int statusChange = checkKey();
  if (flag == 0) {
    if (statusChange == 0){
      banner();
    } else {
      flag = 1;
    }
  } else {
    if (statusChange == 1) {
      if ((keyChange[0] == 1) && (keyStatus[0] == LOW)) {
        cnt ++;
      } else if ((keyChange[1] == 1) && (keyStatus[1] == LOW)) {
        cnt --;
      } else if ((keyChange[2] == 1) && (keyStatus[2] == LOW)) {
        cnt = 0;
      }
    }
    if (cnt > 10000) {
       cnt = 0;
    } else if (cnt < 0) {
        cnt = 0;
    }
    mySseg.writeNum(cnt);
    mySseg.updateOnce();
  }  
}

#define KEY_COUNT_TH 10

int checkKey() {
  int change = 0;
  static uint8_t keys[] = { A1, A2, A3};
  static uint8_t keyCount [] = {0, 0, 0};
  int reading;
  for (uint8_t i = 0 ; i < sizeof(keys) ; i++ ) {
    keyChange[i] = 0;
    if (keyCount[i] > 0) {
      keyCount[i] --;
      if (keyCount[i] == 0) {
        reading = digitalRead(keys[i]);
        if (reading != keyStatus[i]) {
          keyStatus[i] = reading;
          keyChange[i] = 1;
          change = 1;
        }
      }
    } else {
      reading = digitalRead(keys[i]);
      if (reading != keyStatus[i]) {
        keyCount[i] = KEY_COUNT_TH;
      }
    }
  }
  return change;
}

#define OVERWRAP(a, x) (((x) < sizeof(a)) ? (a[(x)]) : a[((x) - sizeof(a))])

uint8_t hello[] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b01101110, // H
  0b00100000, // i
  0b00001110, // t
  0b00010000, // _
  0b00111110, // b
  0b01100000, // l
  0b00111010, // o
  0b00000001
};

void banner() {
  static int p = 0;
  if ((++p) > sizeof(hello))
    p = 0;

  mySseg.writeRawData(
    OVERWRAP(hello, p),
    OVERWRAP(hello, p+1),  
    OVERWRAP(hello, p+2),  
    OVERWRAP(hello, p+3));

  mySseg.updateWithDelay(200);
}


