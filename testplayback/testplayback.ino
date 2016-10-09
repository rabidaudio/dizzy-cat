#include <Wire.h>

#define EADDR 0x50

#define SAMPLE_RATE 125 // *KHz period in useconds

// sin values in thousanths (i) => sin(2*pi*i/1000)
const byte MYSIN[] = {
127,128,129,129,130,131,132,132,133,134,135,136,136,137,138,139,139,140,141,142,143,143,144,145,146,146,147,148,149,149,150,151,152,153,153,154,155,156,156,157,158,159,159,160,161,162,162,163,164,165,165,166,167,168,168,169,170,171,171,172,173,173,
174,175,176,176,177,178,178,179,180,181,181,182,183,183,184,185,185,186,187,188,188,189,190,190,191,192,192,193,194,194,195,196,196,197,198,198,199,199,200,201,201,202,203,203,204,205,205,206,206,207,208,208,209,209,210,211,211,212,212,213,213,214,
215,215,216,216,217,217,218,218,219,220,220,221,221,222,222,223,223,224,224,225,225,226,226,227,227,228,228,229,229,229,230,230,231,231,232,232,233,233,233,234,234,235,235,236,236,236,237,237,238,238,238,239,239,239,240,240,240,241,241,241,242,242,
242,243,243,243,244,244,244,245,245,245,245,246,246,246,247,247,247,247,248,248,248,248,249,249,249,249,249,250,250,250,250,250,251,251,251,251,251,251,252,252,252,252,252,252,252,253,253,253,253,253,253,253,253,253,253,253,254,254,254,254,254,254,
254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,254,253,253,253,253,253,253,253,253,253,253,253,252,252,252,252,252,252,252,251,251,251,251,251,251,250,250,250,250,250,249,249,249,249,249,248,248,248,248,247,
247,247,247,246,246,246,245,245,245,245,244,244,244,243,243,243,242,242,242,241,241,241,240,240,240,239,239,239,238,238,238,237,237,236,236,236,235,235,234,234,233,233,233,232,232,231,231,230,230,229,229,229,228,228,227,227,226,226,225,225,224,224,
223,223,222,222,221,221,220,220,219,218,218,217,217,216,216,215,215,214,213,213,212,212,211,211,210,209,209,208,208,207,206,206,205,205,204,203,203,202,201,201,200,199,199,198,198,197,196,196,195,194,194,193,192,192,191,190,190,189,188,188,187,186,
185,185,184,183,183,182,181,181,180,179,178,178,177,176,176,175,174,173,173,172,171,171,170,169,168,168,167,166,165,165,164,163,162,162,161,160,159,159,158,157,156,156,155,154,153,153,152,151,150,149,149,148,147,146,146,145,144,143,143,142,141,140,
139,139,138,137,136,136,135,134,133,132,132,131,130,129,129,128,127,126,125,125,124,123,122,122,121,120,119,118,118,117,116,115,115,114,113,112,111,111,110,109,108,108,107,106,105,105,104,103,102,101,101,100,99,98,98,97,96,95,95,94,93,92,92,91,90,
89,89,88,87,86,86,85,84,83,83,82,81,81,80,79,78,78,77,76,76,75,74,73,73,72,71,71,70,69,69,68,67,66,66,65,64,64,63,62,62,61,60,60,59,58,58,57,56,56,55,55,54,53,53,52,51,51,50,49,49,48,48,47,46,46,45,45,44,43,43,42,42,41,41,40,39,39,38,38,37,37,36,36,
35,34,34,33,33,32,32,31,31,30,30,29,29,28,28,27,27,26,26,25,25,25,24,24,23,23,22,22,21,21,21,20,20,19,19,18,18,18,17,17,16,16,16,15,15,15,14,14,14,13,13,13,12,12,12,11,11,11,10,10,10,9,9,9,9,8,8,8,7,7,7,7,6,6,6,6,5,5,5,5,5,4,4,4,4,4,3,3,3,3,3,3,2,2,
2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,9,9,9,9,10,10,10,11,11,11,12,12,12,13,13,13,14,14,14,15,15,15,16,16,
16,17,17,18,18,18,19,19,20,20,21,21,21,22,22,23,23,24,24,25,25,25,26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33,34,34,35,36,36,37,37,38,38,39,39,40,41,41,42,42,43,43,44,45,45,46,46,47,48,48,49,49,50,51,51,52,53,53,54,55,55,56,56,57,58,58,59,60,60,
61,62,62,63,64,64,65,66,66,67,68,69,69,70,71,71,72,73,73,74,75,76,76,77,78,78,79,80,81,81,82,83,83,84,85,86,86,87,88,89,89,90,91,92,92,93,94,95,95,96,97,98,98,99,100,101,101,102,103,104,105,105,106,107,108,108,109,110,111,111,112,113,114,115,115,116,
117,118,118,119,120,121,122,122,123,124,125,125,126,
};

double freqs[] = { 261.63, 329.63, 392.00, 523.25, 392.00, 329.63, 261.63 };

int totalClips = 4;
int clipLens[] = {7169, 8098, 6958, 7564};

int i = 0;

boolean x = false;

void setup() {

  // set pin 9 PWM freqency to 31250 Hz
  TCCR2B = TCCR2B & 0b11111000 | 0x04;
  setPwmFrequency(9, 

  // TIMER 1 for interrupt frequency 7812.5 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 7812.5 Hz increments
//  OCR1A = 2047; // = 16000000 / (1 * 7812.5) - 1 (must be <65536)
  OCR1A = 1023;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1 prescaler
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts


//  Serial.begin(9600);
//  Wire.begin();
  pinMode(9, OUTPUT);
  pinMode(29, OUTPUT);
//  analogWrite(9, 0);

  analogWrite(9, 127);
  delay(100);

//  Serial.println(MYSIN[0]);

//  Serial.println(MYSIN[10]);

//  noInterrupts();
}

ISR(TIMER1_COMPA_vect){
   //interrupt commands for TIMER 1 here
   digitalWrite(29, x ? HIGH : LOW);
   x = !x;
}

void loop() {

//  for(int i = 0; i < 7; i++){
//
//    double f = freqs[i];
//
//    for(int n = 0; n < 
//    
//  }
//
//    //round(440.0 * i / 31250.0 * 1000.0)
//    int x = round(f * iii / 31250 * 1000) % 1000;
////    Serial.print(x);
////    Serial.print('\t');
////    Serial.println(MYSIN[x]);
////   Serial.println(MYSIN[round(440.0 * iii / 31250 * 1000) * 1000], DEC);
////  Serial.println(i % 1000);
//
////  analogWrite(9, MYSIN[round(440.0 * iii / 31250 * 1000) * 1000]);
////  analogWrite(9, MYSIN[x]);
//  delayMicroseconds(32);
//  iii++;

//  f += 10;

//  delay(10);
//  delayMicroseconds(500);

//  noInterrupts();
//  for(int j = 0; j < 7; j++){
//    double f = freqs[j];
//    for(int i = 0; i<2000; i++){
//      analogWrite(9, 120*sin(2*PI*f*i/1000) + 128);
//      delayMicroseconds(1000);
//    }
//  }
//  for(int i = 0; i< 50000; i++){
//    analogWrite(9, A[i % 1000]);
//    delayMicroseconds(32);
//  }
//  analogWrite(9, 0);
//  interrupts();

//  delay(1000);
}

void playClip(int clip){
  int start = 0;
  for(int i=0; i<clip;i++){
    start += clipLens[i];
  }

//    Serial.print("play ");
//    Serial.print(start);
//    Serial.print(" -> ");
//    Serial.println(start + clipLens[clip]);

    play(12, start, clipLens[clip]);
}

int buffSize = 4092;
byte playBuffer[4092];

void play(int pin, int startAddr, int len){
  int endAddr = startAddr + len;
  int i = startAddr;
  while(i < endAddr){

    // fill the buffer from i
    int j = min(buffSize, endAddr - i);
    int l = 0;
    while(l < j) {
      int r = min(32, j - l);
      readMax32Bytes(i + l, playBuffer, r);
      l += r;
    }
    // now buffer is from i of length j
    
//    Serial.print('\t');
//    Serial.println(j);
    for(int k = 0; k < j; k++){
      long start = micros();
      analogWrite(pin, i);
      long remain = SAMPLE_RATE - (micros() - start);
      if(remain > 0){
        delayMicroseconds(remain);
      }
    }
    i += j;
  }
  analogWrite(pin, 0);
  
//  for(int i = startAddr; i < startAddr + len; i = i + min(32, startAddr + len - i)){
//    
//    long start = micros();
//    byte b = readByte(i);
//    analogWrite(pin, i);
//    long d = micros() - start;
//    Serial.print("delay: ");
//    Serial.println(d);
//    delay(1);
//
//    if(i > 100){
//      return;
//    }
//    long remain = SAMPLE_RATE - (micros() - start);
//    if(remain > 0){
//      delayMicroseconds(remain);
//    }
//  }
}

void readMax32Bytes(int address, byte* data, int len){
  Wire.beginTransmission(EADDR);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission(true);
  Wire.requestFrom(EADDR, len);
  for(int i = 0; i<len; i++){
    while(Wire.available() == 0) {}
    data[i] = Wire.read();
  }
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

