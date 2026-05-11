#include <Servo.h>

Servo myservo;

const int ledPin = 8;
const int buttonPin = 9;
const int servoPin = 10;

int pos = 0;
int val = 0;

bool lastUpState = HIGH;
bool status = 0;

void setup() {
  
  pinMode(btnUp, INPUT_PULLUP);
  myservo.attach(servoPin);
  Serial.begin(9600);

}

void loop() {

  bool upState = digitalRead(btnUp);

  pos = map(
    0,
    1023,
    0,
    180
  );

  if(lastUpState == HIGH && upState == LOW)
  {
    myservo.write(pos);
  }

  Serial.print("DRS: ");
  Serial.print(status);

}
