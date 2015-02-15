/* MPL1115A2_7seg

 based on http://plaza.rakuten.co.jp/odorie/diary/201012080001/

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
#include <Wire.h>
#include <Sseg.h>

#define I2C_ADDRESS 0x60

short sic11,sic12,sic22,sib1,sib2,sia0;
long sic11l,sic12l,sic22l,sib1l,sib2l,sia0l;

Sseg mySseg = Sseg(4, 8, 11, 13, 14, 2, 10, 12, 3, 6, 7, 9);
// Sseg mySseg = Sseg(4, 8, 11, 13, 14, 5, 10, 12, 3, 6, 7, 9);


void setup() {
  Wire.begin();
  mySseg.begin();
//  Serial.begin(9600);

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.send(0x04);
  Wire.endTransmission();
  Wire.requestFrom(I2C_ADDRESS, 12); // request seven bytes

  if(Wire.available()) {
    short sia0MSB=Wire.receive();
    short sia0LSB= Wire.receive();
    sia0 = sia0MSB <<8; //s16 type //Shift to MSB
    sia0 |= sia0LSB & 0x00FF; //Add LSB to 16bit number
    sia0l = sia0;
    //coeff b1 16bit
    short sib1MSB= Wire.receive();
    short sib1LSB= Wire.receive();
    sib1 = sib1MSB <<8; //Shift to MSB
    sib1 |= sib1LSB & 0x00FF; //Add LSB to 16bit number
    sib1l = sib1;
    //coeff b2 16bit
    short sib2MSB= Wire.receive();
    short sib2LSB= Wire.receive();
    sib2 = sib2MSB <<8; //Shift to MSB
    sib2 |= sib2LSB & 0x00FF; //Add LSB to 16bit number
    sib2 &= 0xFFFF;
    sib2l = sib2;
    //coeff c12 14bit
    short sic12MSB= Wire.receive();
    short sic12LSB= Wire.receive();
    sic12 = sic12MSB <<8; //Shift to MSB only by 8 for MSB
    sic12 |= sic12LSB & 0x00FF;
    sic12l = sic12;
    //coeff c11 11bit
    short sic11MSB= Wire.receive();
    short sic11LSB= Wire.receive();
    sic11 = sic11MSB <<8; //Shift to MSB only by 8 for MSB
    sic11 |= sic11LSB & 0x00FF;
    sic11l = sic11;
    //coeff c22 11bit
    short sic22MSB= Wire.receive();
    short sic22LSB= Wire.receive();
    sic22 = sic22MSB <<8; //Shift to MSB only by 8 for MSB
    sic22 |= sic22LSB & 0x00FF;
    sic22l = sic22;
  }
}

void loop() {
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.send(0x12);
  Wire.send(0x01);
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.send(0x00);
  Wire.endTransmission();
  Wire.requestFrom(I2C_ADDRESS, 4); // request 4 bytes

  if(Wire.available()) {
    short uiPadcw1 = Wire.receive();
    short uiPadcw2 = Wire.receive();
    long uiPadc = uiPadcw1 << 8;
    uiPadc |= uiPadcw2;
    uiPadc &= 0xFFFF;
    uiPadc >>=6;

    short uiTadcw1 = Wire.receive();
    short uiTadcw2 = Wire.receive();
    long uiTadc = uiTadcw1 << 8;
    uiTadc |= uiTadcw2;
    uiTadc &= 0xFFFF;
    uiTadc >>=6;

    long a1 = sib1l + (sic11l*uiPadc /2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0) + (sic12l*uiTadc/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0);
    long a2 = (sib2l/2.0) + (sic22l*uiTadc/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0/2.0);
    float pcomp = sia0l/8.0 + (a1*uiPadc + a2*uiTadc)/8192.0;

    float hPa = (1150.0-500.0)/1023.0*pcomp + 500.0;

    mySseg.writeNum((int)hPa);
    mySseg.updateWithDelay(200);
//  Serial.print("BARO=");
//    Serial.println(hPa);
  }
}

