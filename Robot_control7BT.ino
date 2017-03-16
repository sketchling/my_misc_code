#include <AFMotor.h>
#include <SoftwareSerial.h>
#include <Servo.h>

int pos = 0;
Servo myServo;

SoftwareSerial mySerial(A5, A4); // RX, TX
bool commands_waiting = false;
AF_DCMotor motor(1);
AF_DCMotor rot_motor(2);

//String serialInput = "STRT,F001,R045,B001,L001,Z001,END!,X000";
String serialInput = "";

const int F = 70;
const int B = 66;
const int L = 76;
const int R = 82;
const int Z = 90;

const int LEDpin = LED_BUILTIN;   
char commandChar;
String currentCommand = ""; 

String subString;
int currentValue;

void flashLED(int flashLength)
  { 
      Serial.println("Flashing");
      Serial.println(flashLength);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(flashLength);
      digitalWrite(LED_BUILTIN, LOW);
    }

void moveRobot(int speed)
  {
    Serial.println("Moving");
    Serial.println("Speed : " + speed);
    //motor.setspeed(speed);
    if (speed < 0) 
      {motor.run(BACKWARD);}
    else 
      {motor.run(FORWARD);}
    
    delay(400);
    motor.run(RELEASE);
    
      
   }
 
  //tell motors ot move robot forward or backward
  

void rotateRobot(int angleToRotate)
  {
  Serial.println("Rotating");
  Serial.println(angleToRotate);
   //rot_motor.setSpeed(abs(angleToRotate));
   if (angleToRotate < 0) 
      {rot_motor.run(BACKWARD);}
    else 
      {rot_motor.run(FORWARD);}
    
    delay(600);
    rot_motor.run(RELEASE);
   
   /*if((angleToRotate <=180) || (angleToRotate >= 0)) {
      myServo.write(angleToRotate);
      delay(1000);
 
  
   //tell motors to rotate with differential power 
  
   }
    */};

void setup() 
  {
  mySerial.begin(9600);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  motor.setSpeed(200); 
  motor.run(RELEASE);

  rot_motor.setSpeed(200); 
  rot_motor.run(RELEASE);
  
  
  pinMode(LEDpin, OUTPUT);
  //myServo.attach(7);
  //myServo.write(90);
  }

void loop() 
  {
 
   if (mySerial.available() > 0) 
      {serialInput = mySerial.readString();
      commands_waiting = true;
      Serial.println(serialInput);
      }
      
      

   if (commands_waiting) {
       for( int i = 0; i<= serialInput.length(); i+=5)  
       {
          currentValue = serialInput.substring(i+1,i+4).toInt();
          currentCommand = serialInput.substring(i,i+4);
          char commandChar = currentCommand[0];
          
 /*        if (currentCommand == "STRT")
              {
              Serial.println("Initiating command sequence...");
             //Serial.println("start " + currentCommand);
              } 
   */          
          switch (commandChar) {
            case F: //Ascii for F
              moveRobot(currentValue); //move robot forward by the specified value
              break;
            
            case B: //Ascii for F
              moveRobot(-currentValue); //move robot forward by the specified value
              break;
       
            case R: //Ascii for F
              rotateRobot(currentValue);
              break;
            
            case Z: //Ascii for Z
              flashLED(currentValue * 10);
              break;  
               
            case L: //Ascii for F
              rotateRobot(-currentValue);
              break;
           } 
          
     
        delay(500);
        } 
        serialInput = "";
        commands_waiting = false;
   }
  }
  

    
 
