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

int yPosition = 90;

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

  //Read data of joystick
  int valx = analogRead(x);
  int valy = analogRead(y);
  int valw = analogRead(w);


  //laser control
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



  // xPosition
  int xPosition = map(valy, 0, 1023, 180, 0);
  int xStand = 90;
  
  
  if(xPosition >= 92 || xPosition <= 86){
    if(xPosition > 90){
      xStand = min(xPosition, 96);
    }else if(xPosition < 90){
      xStand = max(xPosition, 84);
    }
  }else{
    xPosition = 90;
  }
  
  xServo.write(xStand);


  // yPosition
  if(valx >= 540 || valx <= 520){
    if(valx > 536){
      if(yPosition >= 180){
        yPosition = 180;
      }else{
        yPosition+=2;
      }
    }

    if(valx < 536){
      if(yPosition <= 0){
        yPosition = 0;
      }else{
        yPosition-=2;
      }
    }

    yServo.write(yPosition);
    
  }
  
  delay(200);
}   

