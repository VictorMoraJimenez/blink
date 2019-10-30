/*
  Blink
  Turns an LED on for two second, then off for two second, repeatedly.
*/

//Constants 
const int ledPin =  LED_BUILTIN;
const int outPIN = 9;
const int interruptPIN = 0;
const long intervalMs = 2000;
const unsigned long longMax = 4294967295;

//Variables
int state = LOW;
unsigned long prevMs = 0;
unsigned long timeValue = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(outPIN, OUTPUT);
  pinMode(interruptPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPIN),interruptBlink, CHANGE);

}

// the loop function runs over and over again forever
void loop() {
  //When millis () turns 0 after 50 days, the remaining interval is 4294967295-previousMillis+millis()
  if (millis() >= prevMs)
    timeValue = millis()-prevMs;
  else
    timeValue = longMax - prevMs + millis();

  if(timeValue >= intervalMs){
    prevMs = millis();
    state = !state;
    digitalWrite(outPIN, state);
  }
}

// interruption function
void interruptBlink(){
  digitalWrite(ledPin, state);

  //Print time and state to monitor the led state
  Serial.print(millis()/1000);
  if(state) 
    Serial.println("s -> LED ON");
  else
    Serial.println("s -> LED OFF"); 
}
