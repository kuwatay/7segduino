/*** DT22 Humidity sensor 7seg

based on DHT22 library
   http://sheepdogguides.com/arduino/ar3ne1humDHT11.htm


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

#include <DHT22.h>
#define DHT22_PIN 16
// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);// Connect a 4.7K resistor between VCC and the data pin (strong pullup)

int temp;
int humi;
int i;
#define INTERVAL (300)

void setup(void)
{
  mySseg.setKcommon();
  mySseg.begin();
}

void loop(void)
{ 
  DHT22_ERROR_t errorCode;

  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
    case DHT_ERROR_CHECKSUM:
      temp = (int)(myDHT22.getTemperatureC() * 10);
      humi = (int)(myDHT22.getHumidity() * 10);
      break;
    case DHT_BUS_HUNG:
    case DHT_ERROR_NOT_PRESENT:
    case DHT_ERROR_ACK_TOO_LONG:
    case DHT_ERROR_SYNC_TIMEOUT:
    case DHT_ERROR_DATA_TIMEOUT:
    case DHT_ERROR_TOOQUICK:
    break;
  }
  if ((++i) > (INTERVAL * 2)) i=0;
  if (i > INTERVAL) {
    mySseg.writeNum(temp);
    mySseg.setDot(2);
    mySseg.write(0, 0b00011010);  // c
  } else {
    mySseg.writeNum(humi);
    mySseg.setDot(2);
    mySseg.write(0, 0b01101110);  // H
  }
  mySseg.updateWithDelay(3);

}
