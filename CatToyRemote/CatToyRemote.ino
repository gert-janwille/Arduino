/*
 * CAT TOY REMOTE - 5V
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
 * IR
 *  - Digital Pin 11
 *  - GND
 *  - 5V
 *  
 *  Laser (led)
 *    - Pin 13
 *  
 */
#include <IRLib.h>
#include <Servo.h>

int ledPin = 13;

int servoX = 9;
int servoY = 10;

int pos;  
int posy;
        
int Speed;

Servo xServo;
Servo yServo;

IRrecv My_Receiver(11);
IRdecode My_Decoder;

boolean previousButton = false; 
boolean ledState = LOW;

#define RIGHT_ARROW 16734885
#define LEFT_ARROW 16716015
#define OK_ARROW 16726215
#define UP_ARROW 16718055
#define DOWN_ARROW 16730805
#define MORE_ARROW 16754775
#define LESS_ARROW 16769055
#define LED 16761405

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  xServo.attach(servoX);
  yServo.attach(servoY);

  pos = 90;
  posy = 90;
  Speed = 15;   
  xServo.write(pos);

  My_Receiver.enableIRIn();
  
}

void loop() {

  if (My_Receiver.GetResults(&My_Decoder)) {
    My_Decoder.decode(); //Decode the data 
    Serial.println(My_Decoder.value);
       switch(My_Decoder.value){
        case RIGHT_ARROW:  pos=min(180,pos+Speed); break;  //right
        case LEFT_ARROW:  pos=max(0,pos-Speed); break;    //left

        case UP_ARROW:  posy=min(180,pos+Speed); break;  //up
        case DOWN_ARROW:  posy=max(0,pos-Speed); break;    //down
    
        case OK_ARROW:  pos=90; break; //select

        case MORE_ARROW:  Speed=min(20, Speed+1); break;  //more speed
        case LESS_ARROW:  Speed=max(15, Speed-1); break;   // less speed
      }

     My_Receiver.resume(); //Restart the receiver
  }

  boolean currentButton;
  
  if(My_Decoder.value == LED){
    currentButton = true;
  }else{
    currentButton = false;
  }
 
  if(currentButton != previousButton) {
    delay(5);
    if(My_Decoder.value == LED){
      currentButton = true;
    }else{
      currentButton = false;
    }
   }
    if(previousButton == false && currentButton == true) { 
      ledState = !ledState;
  }
  previousButton = currentButton; 
  digitalWrite(ledPin, ledState);
  
  

  xServo.write(pos);
  yServo.write(posy);

  delay(200);
}
