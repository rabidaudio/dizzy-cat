#include <Wire.h>

#define EADDR 0x50

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {

  if(Serial.available()){

    String line = "";

    char c = Serial.read();
    while(c != '\n'){
      if( c > 0){
        line += c;
      }
      c = Serial.read();
    }
    
    int space = line.indexOf(' ');

    if(space >= 0){
      int addr = line.substring(0,space).toInt();
      int val = line.substring(space, line.length()).toInt();
  
      writeByte(addr, val);
      delay(5);
  
      Serial.print(addr, DEC);
      Serial.print(' ');
      byte r = readByte(addr);
      Serial.print((int)r, DEC);
      Serial.print('\n');
    }
  }
  delay(1);
}

void writeByte(int address, byte b){
  Wire.beginTransmission(EADDR);
  Wire.write(address >> 8);
  Wire.write(address & 0xFF);
  Wire.write(b);
  Wire.endTransmission(true);
}

byte readByte(int address){
  Wire.beginTransmission(EADDR);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission(true);
  Wire.requestFrom(EADDR, 0x01);
  while(Wire.available() == 0) {}
  return Wire.read();
}

