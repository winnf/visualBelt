const int pingPin = 7;
const int buzzPin = 9;
volatile int state = LOW;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  attachInterrupt(0, handler
}

void loop() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  //double buzzDelay = cm*100;
  if (cm <=10){
    tone(buzzPin, 1047);
    //delay(buzzDelay);
    //digitalWrite(buzzPin,0);
  
  }
  else if(cm<=20&&cm>10){
    tone(buzzPin,880);
  
  }
  else if(cm<=30&&cm>20){
    tone(buzzPin,784);
  
  }
  else if(cm<=40&&cm>30){
    tone(buzzPin,659.3);
  
  }
  else if(cm<=50&&cm>40){
    tone(buzzPin,587.3);
  
  }
  else if(cm<=60&&cm>50){
    tone(buzzPin,523.3);
  
  }
  else {
    noTone(buzzPin);
  
  }
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  delay(100);

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
)
}