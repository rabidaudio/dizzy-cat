#include "TinyWireM.h"

#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4); // RX, TX

#define EADDR 0x50

const byte cat[] = {
  127,126,127,126,127,126,127,126,127,126,
  127,127,127,127,126,127,126,127,126,127,
  127,126,127,126,127,127,127,126,127,126,
  127,126,127,127,126,126,127,127,126,127,
  127,126,127,127,126,127,127,126,127,127,
  126,127,127,126,126,127,127,126,127,127,
};

void setup() {

  
  TinyWireM.begin();
  mySerial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  mySerial.println("Start read");
  for(int i = 0; i < 60; i++){
    byte b = readByte(i);
    if(b != cat[i]){
      mySerial.print("expected ");mySerial.print(cat[i],DEC);
      mySerial.print(" at ");mySerial.print(i, DEC);
      mySerial.print(" but got "); mySerial.println(b, DEC);
    }else{
      mySerial.println(b, DEC);
    }
  }
  mySerial.println("done");
}

byte readByte(int address){
  TinyWireM.beginTransmission(EADDR);
  TinyWireM.send(highByte(address));
  TinyWireM.send(lowByte(address));
  TinyWireM.endTransmission();
  TinyWireM.requestFrom(EADDR, 0x01);
  while(TinyWireM.available() == 0) {}
  return TinyWireM.receive();
}
