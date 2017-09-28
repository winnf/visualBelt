const int buzzPin = 11;
const int buttonPin = 2;
volatile int state = LOW;
long duration[4];  //Each sensor corresponds to an array element. The duration value corresponds to how far away the sensor is from an object.
const int pingPin[4] = {6,7,8,9};
long cm[4];
long inches[4];
int minCM; //Closest sensor to an obstacle
double tones[4] = {523.3 , 587.3 , 659.3, 784}; //Different pitches to diffrientiate directions
int numBeeps = 4; //For testing # of sensors

void setup() {
  // initialize serial communication:
  //Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); //enable internal pullup resistor
  attachInterrupt(digitalPinToInterrupt(buttonPin),handler,RISING); //Interrupt 0 is mapped to pin 2, signal an interrupt on a change to pin 2

}

void loop() {

  while(state == LOW){
    noTone(buzzPin);//While the system is off
    delay(100);

  }
  for(int i = 0 ; i<numBeeps ; i++){ //loop through all sensors
    pinMode(pingPin[i],OUTPUT);  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    digitalWrite(pingPin[i],LOW); // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    delayMicroseconds(2);
    digitalWrite(pingPin[i], HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin[i],LOW);
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
    pinMode(pingPin[i],INPUT);
    duration[i] = pulseIn(pingPin[i], HIGH);
   }

  // convert the time into a distance
  for(int i = 0; i<numBeeps ; i++){
  inches[i] = microsecondsToInches(duration[i]);
  cm[i] = microsecondsToCentimeters(duration[i]);

  }

  minCM = 0; //find the closest sensor to an obstacle
  for(int i = 1; i<numBeeps ; i++){
    if(cm[i]<=cm[minCM]){
      minCM = i;

    }

  }
  //Output sound based on closest sensor and distance from obstacle
  if (cm[minCM] <=10){
    tone(buzzPin, tones[minCM]); //within 10cm play constant tone

  }
  else if(cm[minCM]<=20&&cm[minCM]>10){ //play tone at variable frequencies. Slower frequency = further away
    tone(buzzPin,tones[minCM]);
    delay(100);
    noTone(buzzPin);
   }
  else if(cm[minCM]<=30&&cm[minCM]>20){
    tone(buzzPin,tones[minCM]);
    delay(200);
    noTone(buzzPin);

  }
  else if(cm[minCM]<=40&&cm[minCM]>30){
    tone(buzzPin,tones[minCM]);
    delay(300);
    noTone(buzzPin);

  }
  else if(cm[minCM]<=50&&cm[minCM]>40){
    tone(buzzPin,tones[minCM]);
    delay(400);
    noTone(buzzPin);

  }
  else if(cm[minCM]<=60&&cm[minCM]>50){
    tone(buzzPin,tones[minCM]);
    delay(500);
    noTone(buzzPin);

  }
  else {
    noTone(buzzPin); //obstacle not close enough, no sound

  }
  /*Serial.print(inches[minCM]);
  Serial.print("in, ");
  Serial.print(cm[minCM]);
  Serial.print("cm ");
  Serial.print(tones[minCM]);
  Serial.print("Hz ");
  Serial.print(minCM);
  Serial.print("minCM ");
  Serial.print("cm(0) ");
  Serial.print(cm[0]);
  Serial.print(" cm(1) ");
  Serial.print(cm[1]);
  Serial.print("cm(2) ");
  Serial.print(cm[2]);
  Serial.print(" cm(3) ");
  Serial.print(cm[3]);
  Serial.println(); */

  delay(100);

}

void handler() {
  //Serial.print(state);
  state = !state;
  //Serial.print(state);
  delay(500);

}
long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;

}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;

}
