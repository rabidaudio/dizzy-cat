#include <Wire.h>

#define EADDR 0x50

byte buff[7170];
//byte buff[32];

void setup() {

  Wire.begin();
  Serial.begin(9600);

  delay(10);

  int j = 0;
  while(j < 7170){

    int chunk = min(7170 - j, 32);

    readMax32Bytes(j, buff, j, chunk);

    j += chunk;
  }

  for(int i=0; i < 7170; i++){
    Serial.println(buff[i], DEC);
  }

}

void loop() {
  
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

void readMax32Bytes(int address, byte* data, uint16_t offset, int len){
  Wire.beginTransmission(EADDR);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission(true);
  Wire.requestFrom(EADDR, len);
  for(int i = 0; i<len; i++){
    while(Wire.available() == 0) {}
    data[offset + i] = Wire.read();
  }
}
