#include <Wire.h>

#define EADDR 0x50

int totalClips = 4;
int clipLens[] = {7169, 8098, 6958, 7564};

const int buffSize = 255;
byte playBuffer[buffSize];
volatile uint16_t playPointer = 0;
uint16_t writePointer = 0;

//volatile uint16_t missed = 0;

void setup() {

  Wire.begin();

  setupTimers();

  pinMode(9, OUTPUT);
  analogWrite(9, 0);

//  Serial.begin(9600);

  for(int i = 0; i < totalClips; i++){
    int start = 0;
    for(int j=0;j<i;j++){
      start += clipLens[j];
    }

    play(start, clipLens[i]);

    delay(1000);
  }

}

void loop() {

}

ISR(TIMER1_COMPA_vect){
   //interrupt commands for TIMER 1 here
   if(playPointer < writePointer){
     analogWrite(9, playBuffer[playPointer % buffSize]);
     playPointer++;
//   }else{
//     missed++;
   }
}

void setupTimers(){
  // set pin 9 PWM freqency to 31250 Hz
  TCCR2B = TCCR2B & 0b11111000 | 0x01;

  // http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html
  // TIMER 1 for interrupt frequency 80000 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 80000 Hz increments
  OCR1A = 249;
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1 prescaler
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  // enable timer compare interrupt
//  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
}

void play(int offset, int len){
  int i;
  int chunk;
  playPointer = 0;
  writePointer = 0;
  
  // fill play buffer
  while(writePointer < buffSize){
    chunk = ((buffSize - writePointer) >= 32) ? 32 : buffSize - writePointer;
    readMax32Bytes(offset + writePointer, playBuffer, buffSize, writePointer, chunk);
    writePointer += chunk;
  }

//  Serial.println("loaded initial");

  // start timer for first batch
  cli();
  TIMSK1 |= (1 << OCIE1A);
  sei();

  uint16_t currentPlayPointer = 0;
  uint16_t toFill;

  while(writePointer < len){

    cli();
    currentPlayPointer = playPointer;
    sei();

//    Serial.print("write pointer "); Serial.println(writePointer, DEC);
//    Serial.print("play pointer "); Serial.println(currentPlayPointer, DEC);

    // keep reading into buffer when space is available
    if((writePointer - currentPlayPointer) < buffSize){

      // space available for overwriting is the buffer size minus what playPointer hasn't gotten to yet
      toFill = buffSize - (writePointer - currentPlayPointer);

      // ... or less if we are at the end of the sample
      if((7170 - writePointer) < buffSize){
        toFill = min(toFill, len - writePointer);
      }
//      Serial.print("to fill "); Serial.println(toFill, DEC);

      i = 0;
      while(i < toFill){
        chunk = ((toFill - i) >= 32) ? 32 : toFill - i;
        readMax32Bytes(offset + writePointer, playBuffer, buffSize, writePointer, chunk);
        writePointer += chunk;
        i += chunk;
      }

    }
    
//    Serial.print("new write pointer "); Serial.println(writePointer, DEC);
//    Serial.println("=====");
  
  }

  // wait for play to finish
  while(playPointer < writePointer){ ; }

  // disable timer
  cli();
  TIMSK1 = 0;
  sei();

//  Serial.println("play complete");

  // turn off speaker
  analogWrite(9, 0);

//  Serial.print("write pointer "); Serial.println(writePointer, DEC);
//  Serial.print("play pointer "); Serial.println(playPointer, DEC);
//  Serial.print("missed "); Serial.println(missed, DEC);
}

void readMax32Bytes(int address, byte* data, int buffSize, uint16_t offset, int len){
  Wire.beginTransmission(EADDR);
  Wire.write(highByte(address));
  Wire.write(lowByte(address));
  Wire.endTransmission(true);
  Wire.requestFrom(EADDR, len);
  for(int i = 0; i<len; i++){
    while(Wire.available() == 0) {}
    data[(offset + i) % buffSize] = Wire.read();
  }
}

