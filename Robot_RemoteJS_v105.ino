#include <AFMotor.h>
#include <SoftwareSerial.h>


int pos = 0;
SoftwareSerial mySerial(A5, A4); // RX, TX
bool commandsWaiting = false;
AF_DCMotor motor_L1(1);
AF_DCMotor motor_R1(4);
AF_DCMotor motor_L2(2);
AF_DCMotor motor_R2(3);


int abs_y = 0;

//String serialInput = "STRT,F001,R045,B001,L001,Z001,END!,X000";
String serialInput = "";
String ts = "";

const int LEDpin = LED_BUILTIN;   

String inputString = "";         // a string to hold incoming data
String controlMode;
String xString = "";
String yString = "";
int xyRatio = 2;

boolean stringComplete = false;  // whether the string is complete

//String subString;
int x_speed = 250;
int y_speed = 250;
int left_speed = 250;
int right_speed = 250;
int absLeft = 0;
int absRight = 0;


char light_state = '0';

void flashLED(int flashLength)
  { 
      Serial.println("Flashing");
      Serial.println(flashLength);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(flashLength);
      digitalWrite(LED_BUILTIN, LOW);
    }



/*void serialEvent() 
  {
   while (Serial.available()) 
   {
     // get the new byte:
     char inChar = (char)mySerial.read();
     Serial.println(inputString);
     // add it to the inputString:
     inputString += inChar;
     // if the incoming character is a newline, set a flag
     // so the main loop can do something about it:
     if (inChar == '\n') 
     {
       
       stringComplete = true;
     }
    }
  }*/

void setup() 
  {
    mySerial.begin(9600);
    Serial.begin(9600);
    while (!Serial) 
    {;
    }  // wait for serial port to connect. Needed for native USB port only

   // reserve 200 bytes for the inputString:
 //  inputString.reserve(200);
  
    
      
    motor_R1.setSpeed(200); 
    motor_R1.run(RELEASE);
  
    motor_L1.setSpeed(200); 
    motor_L1.run(RELEASE);
    
    motor_R2.setSpeed(200); 
    motor_R2.run(RELEASE);
  
    motor_L2.setSpeed(200); 
    motor_L2.run(RELEASE);

 
  /*
    rot_motor.setSpeed(200); 
    rot_motor.run(RELEASE);
    
    */ 
    pinMode(LEDpin, OUTPUT);
  }

void loop() 
  {
     
     
     //wait until the full packet has arrived, then act on it
    
     while (mySerial.available() and stringComplete == false ) 
       {
         // get the new byte: 
         char inChar = (char)mySerial.read();
         if (inChar == 'J' ) 
         {  
            //prevent weird starting mid-way through a packet errors
            commandsWaiting = true;
            inputString = "";
          } 

         if (commandsWaiting) 
         {
          
          
              // add it to the inputString:
             inputString += inChar;
             // if the incoming character is a newline, set a flag
             // so the main loop can do something about it:
         }
         
         if (inChar == 'X' and commandsWaiting and inputString.length() == 9) //Weed out odd incorrect strings over bluetooth
         {
           stringComplete = true;
           commandsWaiting = false;
         }
       }
      // print the string when a newline arrives:
    
    //temp bits so that I dont have to do this via bluetooth
   // stringComplete = true;
  //  inputString = "J2503500X";
    
    if (stringComplete) 
    {
     
     // Parse the Serial string
      serialInput = inputString;
      // clear the string:
   
      inputString = "";
      stringComplete = false;
      
      controlMode = serialInput[0];
      xString = serialInput.substring(1,4);
      yString = serialInput.substring(4,7);
      light_state = serialInput[7];
      //Serial.println("controlMode: "+ controlMode +"| xString: " + xString +"| yString: " + yString +"| light_state: " + light_state);
      x_speed = (xString.toInt())-250; //int comes in 1-500 with 250 being '0' or middle   
      y_speed = (yString.toInt())-250; // same
    
      left_speed = y_speed + x_speed;
      right_speed = y_speed - x_speed;
      
      //Serial.println(" x_speed: "+ x_speed);
     // Serial.println("y_speed: " +y_speed); 
      //Serial.println(" left_speed: " + left_speed);
      //Serial.println(" right_speed: " +right_speed );
  
      /*         
      //deal with X axis:
      motor.setSpeed(abs(x_speed-250));
      if (x_speed < 250) 
        {rot_motor.run(BACKWARD);}
      else if (x_speed > 250) 
        {rot_motor.run(FORWARD);}
      */
      //deal with Y axis:
      
      
      abs_y = abs(y_speed);
      Serial.println(y_speed);
      absLeft = abs(left_speed);
      absRight = abs(right_speed);
      
      
      motor_L1.setSpeed(absLeft);
      motor_L2.setSpeed(absLeft);
      motor_R1.setSpeed(absRight);
      motor_R2.setSpeed(absRight);


      
      if (left_speed < 0) 
        {
          motor_L1.run(FORWARD);
          motor_L2.run(FORWARD);
        }
      else if (left_speed > 0) 
        {
          motor_L1.run(BACKWARD);
          motor_L2.run(BACKWARD);
        }      
        else if (right_speed < 0) 
        {
          motor_L2.run(FORWARD);
          motor_R2.run(FORWARD);
        }
       else if (right_speed > 0) 
        {
          motor_L2.run(BACKWARD);
          motor_R2.run(BACKWARD);
        }
 
  
    }
   // else {Serial.println("string incomplete");}
  
   //   if (x_speed = 250) {motor.run(RELEASE);}
  /*    if (y_speed = 250) 
      {
        motor_L1.run(RELEASE);
        motor_R1.run(RELEASE);   
      }*/
 }
      
  

  

    
 
