//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(4,3); // RX, TX

bool upsideDown = false;

int downThreshold = 480;
int upThreshold = 620;
int center = 535;

int statePin = 1; //3

void setup() {
  analogReference(EXTERNAL);

  pinMode(statePin, OUTPUT);

//  Serial.begin(9600);

//  mySerial.begin(9600);

  int val = analogRead(1);
  upsideDown = (val < center);
  digitalWrite(statePin, upsideDown ? HIGH : LOW);
}

void loop() {
  //upright Z with 3.3V AREF = 640
  // upside down: 430
  // trigger: 480, 620

  int val = analogRead(1);
//  mySerial.println(val, DEC);
  if(upsideDown){
    if(val > upThreshold){
      upsideDown = false;
      digitalWrite(statePin, LOW);
      delay(250); //hacky debounce
    }
  }else{
    if(val < downThreshold){
      upsideDown = true;
      digitalWrite(statePin, HIGH);
      delay(250); //hacky debounce
    }
  }

  delay(50);
}
