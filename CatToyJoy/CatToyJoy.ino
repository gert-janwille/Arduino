/*
 * CAT TOY - 5V
 * 
 * 
 * Servo 360 = X 
 * Servo 180 = y
 * 
 * Servo 360
 *  - black -> GND
 *  - red -> VCC
 *  - white -> Digital Pin 9
 *  
 * Servo 180
 *  - brown -> GND
 *  - red -> VCC
 *  - orange -> Digital Pin 10
 *  
 *  
 * Joystick
 *  - 5V
 *  - VRx -> Analog 0
 *  - VRy -> Analog 1
 *  - SW -> Analog 2
 *  
 *  Laser (led)
 *    - Pin 13
 *  
 */
#include <Servo.h>

int ledPin = 13;

int servoX = 9;
int servoY = 10;

int x = 0;
int y = 1;
int w = 2;

Servo xServo;
Servo yServo;

boolean previousButton = false; 
boolean ledState = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(w, INPUT);

  pinMode(ledPin, OUTPUT);

  xServo.attach(servoX);
  yServo.attach(servoY);
  
}

void loop() {

  int valx = analogRead(x);
  int valy = analogRead(y);
  int valw = analogRead(w);

  boolean currentButton;
  
  if(valw == 0){
    currentButton = true;
  }else{
    currentButton = false;
  }
 
  if(currentButton != previousButton) {
    delay(5);
    if(valw == 0){
      currentButton = true;
    }else{
      currentButton = false;
    }
   }
    if(previousButton == false && currentButton == HIGH) { 
      ledState = !ledState;
  }
  previousButton = currentButton; 
  digitalWrite(ledPin, ledState);
  
  int position = map(valy, 0, 1023, 180, 0);
  if(position == 86){
    position = 90;
  }
  
  xServo.write(position);
  yServo.write(map(valx, 0, 1025, 0, 180));
  delay(200);
}
