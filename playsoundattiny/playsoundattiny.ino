
bool x = false;

void setup() {

  pinMode(0, OUTPUT);
  

  // TIMER 1 for interrupt frequency 7812.5 Hz:
  cli(); // stop interrupts
  TCCR1 = 0; // set entire TCCR1A register to 0
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 7812.5 Hz increments
  OCR1C = 2047; // = 16000000 / (1 * 7812.5) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1 |= (1 << CTC1);
  // Set CS12, CS11 and CS10 bits for 1 prescaler
  TCCR1 |= (0 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK |= (1 << OCIE1A);
  sei(); // allow interrupts


}

ISR(TIMER1_COMPA_vect){
   //interrupt commands for TIMER 1 here
   digitalWrite(0, x ? HIGH : LOW);
   x = !x;
}


void loop() {

}
